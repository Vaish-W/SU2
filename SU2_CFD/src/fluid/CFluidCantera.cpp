/*!
 * \file CFluidCantera.cpp
 * \brief Defines the multicomponent incompressible Ideal Gas model for reacting flows.
 * \author T. Economon, Cristopher Morales Ubal
 * \version 8.1.0 "Harrier"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2024, SU2 Contributors (cf. AUTHORS.md)
 *
 * SU2 is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * SU2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with SU2. If not, see <http://www.gnu.org/licenses/>.
 */

#include "../../include/fluid/CFluidCantera.hpp"

#include <cmath>

#include <numeric>
#ifdef USE_CANTERA
#include "../../Common/include/basic_types/ad_structure.hpp"

#include "/home/cristopher/codes/cantera/include/cantera/core.h"
#include "/home/cristopher/codes/cantera/include/cantera/kinetics/Reaction.h"
#include <fstream>
#include <iostream>

using namespace Cantera;
using namespace SU2_TYPE;
#endif

CFluidCantera::CFluidCantera(su2double value_pressure_operating, const CConfig* config)
    : CFluidModel(),
      n_species_mixture(config->GetnSpecies() + 1),
      Pressure_Thermodynamic(value_pressure_operating),
      GasConstant_Ref(config->GetGas_Constant_Ref()),
      Prandtl_Number(config->GetPrandtl_Turb()),
      Transport_Model(config->GetTransport_Model()),
      Chemical_MechanismFile(config->GetChemical_MechanismFile()),
      Phase_Name(config->GetPhase_Name()){
  if (n_species_mixture > ARRAYSIZE) {
    SU2_MPI::Error("Too many species, increase ARRAYSIZE", CURRENT_FUNCTION);
  }

  #ifdef USE_CANTERA
  sol = std::shared_ptr<Cantera::Solution>(newSolution(Chemical_MechanismFile, Phase_Name, Transport_Model));
  sol->thermo()->getMolecularWeights(&molarMasses[0]);
  for (int iVar = 0; iVar < n_species_mixture; iVar++) { 
    gasComposition[iVar]=config->GetChemical_GasComposition(iVar);
    //config->SetChemical_GasComposition(iVar, gasComposition[iVar]); //this should be used for later
  }
  #endif

  SetMassDiffusivityModel(config);
}

void CFluidCantera::SetMassDiffusivityModel(const CConfig* config) {
  for (int iVar = 0; iVar < n_species_mixture; iVar++) {
    MassDiffusivityPointers[iVar] = MakeMassDiffusivityModel(config, iVar);
  }
}

#ifdef USE_CANTERA
void CFluidCantera::ComputeMassDiffusivity() {
  int nsp = sol->thermo()->nSpecies();
  vector<su2double> diff(nsp);
  sol->transport()->getMixDiffCoeffsMass(&diff[0]);
  for (int iVar = 0; iVar < n_species_mixture; iVar++) {
    massDiffusivity[iVar] = diff[sol->thermo()->speciesIndex(gasComposition[iVar])];
  }
}

void CFluidCantera::ComputeChemicalSourceTerm(){
  vector<su2double> netProductionRates(sol->kinetics()->nReactions());
  sol->kinetics()->getNetProductionRates(&netProductionRates[0]);
  for (int iVar = 0; iVar < n_species_mixture; iVar++) {
    int speciesIndex = sol->thermo()->speciesIndex(gasComposition[iVar]);
    chemicalSourceTerm[iVar] = molarMasses[speciesIndex]*netProductionRates[speciesIndex];
  }
}

void CFluidCantera::ComputeHeatRelease(){
  vector<su2double> netProductionRates(sol->kinetics()->nReactions());
  vector<su2double> partialMolarEnthalpies(sol->thermo()->nSpecies());
  sol->kinetics()->getNetProductionRates(&netProductionRates[0]);
  sol->thermo()->getPartialMolarEnthalpies(&partialMolarEnthalpies[0]);
  Heat_Release = 0.0;
  for (int iVar = 0; iVar < n_species_mixture; iVar++) {
    int speciesIndex = sol->thermo()->speciesIndex(gasComposition[iVar]);
    Heat_Release += partialMolarEnthalpies[speciesIndex]*netProductionRates[speciesIndex];
  }
}

void CFluidCantera::GetEnthalpyDiffusivity(su2double* enthalpy_diffusions) {
  const int nsp = sol->thermo()->nSpecies();
  // The universal gas constant times temperature is retrieved from cantera.
  const su2double uni_gas_constant_temp = sol->thermo()->RT();
  vector<su2double> enthalpiesSpecies(nsp);
  vector<su2double> diff(nsp);
  sol->thermo()->getEnthalpy_RT_ref(&enthalpiesSpecies[0]);
  sol->transport()->getMixDiffCoeffsMass(&diff[0]);
  const int speciesN = sol->thermo()->speciesIndex(gasComposition[n_species_mixture - 1]);
  for (int iVar = 0; iVar < n_species_mixture - 1; iVar++) {
    int speciesIndex = sol->thermo()->speciesIndex(gasComposition[iVar]);
    enthalpy_diffusions[iVar] = Density * uni_gas_constant_temp *
                                ((enthalpiesSpecies[speciesIndex] * diff[speciesIndex] / molarMasses[speciesIndex]) -
                                 (enthalpiesSpecies[speciesN] * diff[speciesN] / molarMasses[speciesN]));
  }
}

void CFluidCantera::GetGradEnthalpyDiffusivity(su2double* grad_enthalpy_diffusions) {
  const int nsp = sol->thermo()->nSpecies();
  // The universal gas constant is retrieved from cantera,in order to keep consistency with the values retrieve from it.
  const su2double universal_gas_constant = (sol->thermo()->RT()) / Temperature;
  vector<su2double> specificHeatSpecies(nsp);
  vector<su2double> diff(nsp);
  sol->thermo()->getCp_R_ref(&specificHeatSpecies[0]);
  sol->transport()->getMixDiffCoeffsMass(&diff[0]);
  const int speciesN = sol->thermo()->speciesIndex(gasComposition[n_species_mixture - 1]);
  for (int iVar = 0; iVar < n_species_mixture - 1; iVar++) {
    int speciesIndex = sol->thermo()->speciesIndex(gasComposition[iVar]);
    grad_enthalpy_diffusions[iVar] = Density * universal_gas_constant *
                               ((specificHeatSpecies[speciesIndex] * diff[speciesIndex] / molarMasses[speciesIndex]) -
                                (specificHeatSpecies[speciesN] * diff[speciesN] / molarMasses[speciesN]));
  }
}

void CFluidCantera::ComputeTempFromEnthalpy(const su2double val_enthalpy, su2double* val_temperature,
                                            const su2double* val_scalars) {
  DictionaryChemicalComposition(val_scalars);
  /*--- convergence criterion for temperature in [K], high accuracy needed for restarts. ---*/
  su2double toll = 1e-5;
  su2double temp_iter = 300.0;
  su2double delta_temp_iter = 1e10;
  su2double delta_enthalpy_iter;
  const int counter_limit = 20;

  int counter = 0;

  while ((abs(delta_temp_iter) > toll) && (counter++ < counter_limit)) {
    /*--- Set thermodynamic state based on the current value of temperature. ---*/
    sol->thermo()->setState_TPY(GetValue(temp_iter), GetValue(Pressure_Thermodynamic), chemical_composition);

    su2double Enthalpy = sol->thermo()->enthalpy_mass();
    su2double Cp = sol->thermo()->cp_mass();

    delta_enthalpy_iter = val_enthalpy - Enthalpy;

    delta_temp_iter = delta_enthalpy_iter / Cp;

    temp_iter += delta_temp_iter;
    if (temp_iter < 0.0) {
      cout << "Warning: Negative temperature has been found during Newton-Raphson" << endl;
      break;
    }
  }
  *val_temperature = temp_iter;
  if (counter == counter_limit) {
    cout << "Warning Newton-Raphson exceed number of max iteration in temperature computation" << endl;
  }
}

string CFluidCantera::DictionaryChemicalComposition(const su2double* val_scalars) {
  su2double val_scalars_sum{0.0};
  chemical_composition="";
  for (int i_scalar = 0; i_scalar < n_species_mixture - 1; i_scalar++) {
    chemical_composition.append(gasComposition[i_scalar] + ":" + to_string(val_scalars[i_scalar])+", ");
    val_scalars_sum += val_scalars[i_scalar];
  }
  chemical_composition.append(gasComposition[n_species_mixture - 1] + ":" + to_string(1.0 - val_scalars_sum));

  return chemical_composition;
}

void CFluidCantera::SetTDState_T(const su2double val_temperature, const su2double* val_scalars) {
  DictionaryChemicalComposition(val_scalars);
  Temperature = val_temperature;
  sol->thermo()->setState_TPY(GetValue(Temperature), GetValue(Pressure_Thermodynamic), chemical_composition);
  Density = sol->thermo()->density();
  Enthalpy = sol->thermo()->enthalpy_mass();
  Cp = sol->thermo()->cp_mass();
  Cv = sol->thermo()->cv_mass();
  Mu = sol->transport()->viscosity();
  Kt = sol->transport()->thermalConductivity();

  ComputeMassDiffusivity();
  ComputeChemicalSourceTerm();
  ComputeHeatRelease();
}
#endif