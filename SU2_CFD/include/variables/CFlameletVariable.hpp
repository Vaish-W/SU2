/*!
 * \file CFlameletVariable.hpp
 * \brief Declaration of the variables of the flamelet model.
 * \author D. Mayer, T. Economon
 * \version 6.2.0 "Falcon"
 *
 * The current SU2 release has been coordinated by the
 * SU2 International Developers Society <www.su2devsociety.org>
 * with selected contributions from the open-source community.
 *
 * The main research teams contributing to the current release are:
 *  - Prof. Juan J. Alonso's group at Stanford University.
 *  - Prof. Piero Colonna's group at Delft University of Technology.
 *  - Prof. Nicolas R. Gauger's group at Kaiserslautern University of Technology.
 *  - Prof. Alberto Guardone's group at Polytechnic University of Milan.
 *  - Prof. Rafael Palacios' group at Imperial College London.
 *  - Prof. Vincent Terrapon's group at the University of Liege.
 *  - Prof. Edwin van der Weide's group at the University of Twente.
 *  - Lab. of New Concepts in Aeronautics at Tech. Institute of Aeronautics.
 *
 * Copyright 2012-2019, Francisco D. Palacios, Thomas D. Economon,
 *                      Tim Albring, and the SU2 contributors.
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

#pragma once

#include "CScalarVariable.hpp"

/*!
 * \class CFlameletVariable
 * \brief Main class for defining the variables of the flamelet model.
 * \author D. Mayer, T. Economon
 */
class CFlameletVariable final : public CScalarVariable {
protected:
  //MatrixType source_prog;            /*!< \brief Vector of the source terms from the lookup table for each scalar equation */
  MatrixType source_scalar;          /*!< \brief Vector of the source terms from the lookup table for each scalar equation */
  MatrixType lookup_scalar;          /*!< \brief Vector of the source terms from the lookup table for each scalar equation */
  //MatrixType source_scalar_rescaled; /*!< \brief Vector of the source terms from the lookup table for each scalar equation */
  //MatrixType scalar_table_paraview;  /*!< \brief Vector of the values of the scalar from the lookup table for visualization */
  
public:
  /*!
   * \brief Constructor of the class.
   * \param[in] val_scalar_inf - Scalar variable value (initialization value).
   * \param[in] npoint         - Number of points/nodes/vertices in the domain.
   * \param[in] ndim           - Number of dimensions of the problem.
   * \param[in] nvar           - Number of variables of the problem.
   * \param[in] config         - Definition of the particular problem.
   */
  CFlameletVariable(su2double     *val_scalar_inf,
                    unsigned long npoint,
                    unsigned long ndim,
                    unsigned long nvar,
                    CConfig       *config);
  
  /*!
   * \brief Destructor of the class.
   */
  ~CFlameletVariable() = default;
  
    
  /*!
   * \brief Set the value of the transported scalar source term
   * \param[in] val_- the .
   * \param[in] val_ivar        - eqn. index to the .
   */
  inline void SetSourceScalar(unsigned long  iPoint,
                            su2double      val_source_scalar,
                            unsigned short val_ivar) override {
    source_scalar(iPoint,val_ivar) = val_source_scalar;
  }
  
  /*!
   * \brief Set the value of the transported scalar source term
   * \param[in] val_- the .
   * \param[in] val_ivar        - eqn. index to the .
   */
  inline void SetLookupScalar(unsigned long  iPoint,
                            su2double      val_lookup_scalar,
                            unsigned short val_ivar) override {
    lookup_scalar(iPoint,val_ivar) = val_lookup_scalar;
  }

  /*!
   * \brief Get the value of the transported scalar source term
   * \param[in] val_ivar - eqn. index to the transported scalar source term
   * \return Value of the progress variable source term
   */
  inline su2double GetSourceScalar(unsigned long  iPoint,
                                 unsigned short val_ivar) override {
    return source_scalar(iPoint,val_ivar);
  }

   /*!
   * \brief Get the value of the looked up scalar field
   * \param[in] val_ivar - eqn. index to the looked up scalar field
   * \return Value of the looked up scalar field
   */
  inline su2double GetLookupScalar(unsigned long  iPoint,
                                 unsigned short val_ivar) override {
    return lookup_scalar(iPoint,val_ivar);
  }
  

  /*!
   * \brief Get the value of the transported scalars source term
   * \return Pointer to the transported scalars source term
   */
  inline su2double *GetSourceScalar(unsigned long iPoint) override {
    return source_scalar[iPoint];
  }

  /*!
   * \brief Get the value of the looked up table based on the transported scalar
   * \return Pointer to the transported scalars source term
   */
  inline su2double *GetLookupScalar(unsigned long iPoint) override {
    return lookup_scalar[iPoint];
  }
  
  
};