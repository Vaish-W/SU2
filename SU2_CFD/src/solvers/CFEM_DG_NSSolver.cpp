/*!
 * \file CFEM_DG_NSSolver.cpp
 * \brief Main subroutines for solving finite element Navier-Stokes flow problems
 * \author J. Alonso, E. van der Weide, T. Economon
 * \version 7.1.0 "Blackbird"
 *
 * SU2 Project Website: https://su2code.github.io
 *
 * The SU2 Project is maintained by the SU2 Foundation
 * (http://su2foundation.org)
 *
 * Copyright 2012-2020, SU2 Contributors (cf. AUTHORS.md)
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


#include "../../include/solvers/CFEM_DG_NSSolver.hpp"

CFEM_DG_NSSolver::CFEM_DG_NSSolver(CGeometry      *geometry,
                                   CConfig        *config,
                                   unsigned short iMesh)
 : CFEM_DG_EulerSolver(geometry, config, iMesh) {

  /*--- Check if the symmetrizing terms are present. ---*/
  if(fabs(config->GetTheta_Interior_Penalty_DGFEM()) > 1.e-8)
    symmetrizingTermsPresent = true;

  /*--- Get the viscous data at the farfield from config. ---*/
  Viscosity_Inf = config->GetViscosity_FreeStreamND();
  Prandtl_Lam   = config->GetPrandtl_Lam();
  Prandtl_Turb  = config->GetPrandtl_Turb();
  Tke_Inf       = config->GetTke_FreeStreamND();

  /*--- Set the SGS model in case an LES simulation is carried out ---*/
  if(config->GetKind_Solver() == FEM_LES) {

    /*--- Make a distinction between the SGS models used and set SGSModel and
          SGSModelUsed accordingly. ---*/
    switch( config->GetKind_SGS_Model() ) {

      case IMPLICIT_LES:
        SGSModel     = nullptr;
        SGSModelUsed = false;
        break;

      case SMAGORINSKY:
        SGSModel     = new CSmagorinskyModel;
        SGSModelUsed = true;
        break;

      case WALE:
        SGSModel     = new CWALEModel;
        SGSModelUsed = true;
        break;

      case VREMAN:
        SGSModel     = new CVremanModel;
        SGSModelUsed = true;
        break;

      default:
        SU2_MPI::Error(string("Unknown SGS model encountered"),
                       CURRENT_FUNCTION);
    }
  }
}

CFEM_DG_NSSolver::~CFEM_DG_NSSolver(void) {

  delete SGSModel;
}

void CFEM_DG_NSSolver::Friction_Forces(const CGeometry *geometry, const CConfig *config) {
  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::SetTime_Step(CGeometry *geometry, CSolver **solver_container, CConfig *config,
                                    unsigned short iMesh, unsigned long Iteration) {
  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ADER_DG_AliasedPredictorResidual_2D(CConfig              *config,
                                                           CVolumeElementFEM_DG *elem,
                                                           const su2double      *sol,
                                                           const unsigned short nSimul,
                                                           const unsigned short NPad,
                                                           su2double            *res,
                                                           su2double            *work) {
  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ADER_DG_AliasedPredictorResidual_3D(CConfig              *config,
                                                           CVolumeElementFEM_DG *elem,
                                                           const su2double      *sol,
                                                           const unsigned short nSimul,
                                                           const unsigned short NPad,
                                                           su2double            *res,
                                                           su2double            *work) {
  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ADER_DG_NonAliasedPredictorResidual_2D(CConfig              *config,
                                                              CVolumeElementFEM_DG *elem,
                                                              const su2double      *sol,
                                                              const unsigned short nSimul,
                                                              const unsigned short NPad,
                                                              su2double            *res,
                                                              su2double            *work) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ADER_DG_NonAliasedPredictorResidual_3D(CConfig              *config,
                                                              CVolumeElementFEM_DG *elem,
                                                              const su2double      *sol,
                                                              const unsigned short nSimul,
                                                              const unsigned short NPad,
                                                              su2double            *res,
                                                              su2double            *work) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::Shock_Capturing_DG(CConfig             *config,
                                          const unsigned long elemBeg,
                                          const unsigned long elemEnd,
                                          su2double           *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}
void CFEM_DG_NSSolver::Shock_Capturing_DG_Persson(const unsigned long elemBeg,
                                                  const unsigned long elemEnd,
                                                  su2double           *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::Volume_Residual(CConfig             *config,
                                       const unsigned long elemBeg,
                                       const unsigned long elemEnd,
                                       su2double           *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ResidualFaces(CConfig             *config,
                                     const unsigned long indFaceBeg,
                                     const unsigned long indFaceEnd,
                                     unsigned long       &indResFaces,
                                     CNumerics           *numerics,
                                     su2double           *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ViscousNormalFluxFace(const CVolumeElementFEM_DG *adjVolElem,
                                             const unsigned short       indFaceChunk,
                                             const unsigned short       nInt,
                                             const unsigned short       NPad,
                                             const su2double            Wall_HeatFlux,
                                             const bool                 HeatFlux_Prescribed,
                                             const su2double            *solInt,
                                             const su2double            *gradSolInt,
                                             const su2double            *metricCoorDerivFace,
                                             const su2double            *metricNormalsFace,
                                             const su2double            *wallDistanceInt,
                                                   su2double            *viscNormFluxes,
                                                   su2double            *viscosityInt,
                                                   su2double            *kOverCvInt) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ViscousNormalFluxIntegrationPoint_2D(const su2double *sol,
                                                            const su2double solGradCart[4][2],
                                                            const su2double *normal,
                                                            const su2double HeatFlux,
                                                            const su2double factHeatFlux,
                                                            const su2double wallDist,
                                                            const su2double lenScale_LES,
                                                                  su2double &Viscosity,
                                                                  su2double &kOverCv,
                                                                  su2double *normalFlux) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ViscousNormalFluxIntegrationPoint_3D(const su2double *sol,
                                                            const su2double solGradCart[5][3],
                                                            const su2double *normal,
                                                            const su2double HeatFlux,
                                                            const su2double factHeatFlux,
                                                            const su2double wallDist,
                                                            const su2double lenScale_LES,
                                                                  su2double &Viscosity,
                                                                  su2double &kOverCv,
                                                                  su2double *normalFlux) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::PenaltyTermsFluxFace(const unsigned short indFaceChunk,
                                            const unsigned short nInt,
                                            const unsigned short NPad,
                                            const su2double      *solInt0,
                                            const su2double      *solInt1,
                                            const su2double      *viscosityInt0,
                                            const su2double      *viscosityInt1,
                                            const su2double      *kOverCvInt0,
                                            const su2double      *kOverCvInt1,
                                            const su2double      ConstPenFace,
                                            const su2double      lenScale0,
                                            const su2double      lenScale1,
                                            const su2double      *metricNormalsFace,
                                                  su2double      *penaltyFluxes) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::SymmetrizingFluxesFace(const unsigned short indFaceChunk,
                                              const unsigned short nInt,
                                              const unsigned short NPad,
                                              const su2double      *solInt0,
                                              const su2double      *solInt1,
                                              const su2double      *viscosityInt0,
                                              const su2double      *viscosityInt1,
                                              const su2double      *kOverCvInt0,
                                              const su2double      *kOverCvInt1,
                                              const su2double      *metricNormalsFace,
                                                    su2double      *symmFluxes) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::TransformSymmetrizingFluxes(const unsigned short indFaceChunk,
                                                   const unsigned short nInt,
                                                   const unsigned short NPad,
                                                   const su2double      halfTheta,
                                                   const su2double      *symmFluxes,
                                                   const su2double      *weights,
                                                   const su2double      *metricCoorFace,
                                                         su2double      *paramFluxes) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Euler_Wall(CConfig                  *config,
                                     const unsigned long      surfElemBeg,
                                     const unsigned long      surfElemEnd,
                                     const CSurfaceElementFEM *surfElem,
                                     su2double                *resFaces,
                                     CNumerics                *conv_numerics,
                                     su2double                *workArray){

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Far_Field(CConfig                  *config,
                                    const unsigned long      surfElemBeg,
                                    const unsigned long      surfElemEnd,
                                    const CSurfaceElementFEM *surfElem,
                                    su2double                *resFaces,
                                    CNumerics                *conv_numerics,
                                    su2double                *workArray){

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Sym_Plane(CConfig                  *config,
                                    const unsigned long      surfElemBeg,
                                    const unsigned long      surfElemEnd,
                                    const CSurfaceElementFEM *surfElem,
                                    su2double                *resFaces,
                                    CNumerics                *conv_numerics,
                                    su2double                *workArray){

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Supersonic_Outlet(CConfig                  *config,
                                            const unsigned long      surfElemBeg,
                                            const unsigned long      surfElemEnd,
                                            const CSurfaceElementFEM *surfElem,
                                            su2double                *resFaces,
                                            CNumerics                *conv_numerics,
                                            su2double                *workArray){

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Inlet(CConfig                  *config,
                                const unsigned long      surfElemBeg,
                                const unsigned long      surfElemEnd,
                                const CSurfaceElementFEM *surfElem,
                                su2double                *resFaces,
                                CNumerics                *conv_numerics,
                                unsigned short           val_marker,
                                su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Outlet(CConfig                  *config,
                                 const unsigned long      surfElemBeg,
                                 const unsigned long      surfElemEnd,
                                 const CSurfaceElementFEM *surfElem,
                                 su2double                *resFaces,
                                 CNumerics                *conv_numerics,
                                 unsigned short           val_marker,
                                 su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_HeatFlux_Wall(CConfig                  *config,
                                        const unsigned long      surfElemBeg,
                                        const unsigned long      surfElemEnd,
                                        const CSurfaceElementFEM *surfElem,
                                        su2double                *resFaces,
                                        CNumerics                *conv_numerics,
                                        unsigned short           val_marker,
                                        su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Isothermal_Wall(CConfig                  *config,
                                          const unsigned long      surfElemBeg,
                                          const unsigned long      surfElemEnd,
                                          const CSurfaceElementFEM *surfElem,
                                          su2double                *resFaces,
                                          CNumerics                *conv_numerics,
                                          unsigned short           val_marker,
                                          su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Riemann(CConfig                  *config,
                                  const unsigned long      surfElemBeg,
                                  const unsigned long      surfElemEnd,
                                  const CSurfaceElementFEM *surfElem,
                                  su2double                *resFaces,
                                  CNumerics                *conv_numerics,
                                  unsigned short           val_marker,
                                  su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::BC_Custom(CConfig                  *config,
                                 const unsigned long      surfElemBeg,
                                 const unsigned long      surfElemEnd,
                                 const CSurfaceElementFEM *surfElem,
                                 su2double                *resFaces,
                                 CNumerics                *conv_numerics,
                                 su2double                *workArray) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ViscousBoundaryFacesBCTreatment(
                                       CConfig                  *config,
                                       CNumerics                *conv_numerics,
                                       const unsigned short     nFaceSimul,
                                       const unsigned short     NPad,
                                       const su2double          Wall_HeatFlux,
                                       const bool               HeatFlux_Prescribed,
                                       const su2double          Wall_Temperature,
                                       const bool               Temperature_Prescribed,
                                       const CSurfaceElementFEM *surfElem,
                                       const su2double          *solIntL,
                                       const su2double          *solIntR,
                                             su2double          *workArray,
                                             su2double          *resFaces,
                                             unsigned long      &indResFaces,
                                             CWallModel         *wallModel) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ComputeViscousFluxesBoundaryFaces(
                                       CConfig                  *config,
                                       const unsigned short     nFaceSimul,
                                       const unsigned short     NPad,
                                       const unsigned short     nInt,
                                       const unsigned short     nDOFsElem,
                                       const su2double          Wall_HeatFlux,
                                       const bool               HeatFlux_Prescribed,
                                       const su2double          *derBasisElem,
                                       const CSurfaceElementFEM *surfElem,
                                       const su2double          *solIntL,
                                             su2double          *solElem,
                                             su2double          *gradSolInt,
                                             su2double          *viscFluxes,
                                             su2double          *viscosityInt,
                                             su2double          *kOverCvInt) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::WallTreatmentViscousFluxes(
                                  CConfig                  *config,
                                  const unsigned short     nFaceSimul,
                                  const unsigned short     NPad,
                                  const unsigned short     nInt,
                                  const su2double          Wall_HeatFlux,
                                  const bool               HeatFlux_Prescribed,
                                  const su2double          Wall_Temperature,
                                  const bool               Temperature_Prescribed,
                                  const CSurfaceElementFEM *surfElem,
                                  const su2double          *solIntL,
                                        su2double          *workArray,
                                        su2double          *viscFluxes,
                                        su2double          *viscosityInt,
                                        su2double          *kOverCvInt,
                                        CWallModel         *wallModel) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}

void CFEM_DG_NSSolver::ResidualViscousBoundaryFace(
                                      CConfig                  *config,
                                      CNumerics                *conv_numerics,
                                      const unsigned short     nFaceSimul,
                                      const unsigned short     NPad,
                                      const CSurfaceElementFEM *surfElem,
                                      const su2double          *solInt0,
                                      const su2double          *solInt1,
                                      su2double                *paramFluxes,
                                      su2double                *fluxes,
                                      su2double                *viscFluxes,
                                      const su2double          *viscosityInt,
                                      const su2double          *kOverCvInt,
                                      su2double                *resFaces,
                                      unsigned long            &indResFaces) {

  SU2_MPI::Error(string("Not implemented yet"), CURRENT_FUNCTION);
}
