/* =============================================================================
**  This file is part of the mmg software package for the tetrahedral
**  mesh modification.
**  Copyright (c) Inria - IMB (Université de Bordeaux) - LJLL (UPMC), 2004- .
**
**  mmg is free software: you can redistribute it and/or modify it
**  under the terms of the GNU Lesser General Public License as published
**  by the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**
**  mmg is distributed in the hope that it will be useful, but WITHOUT
**  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
**  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
**  License for more details.
**
**  You should have received a copy of the GNU Lesser General Public
**  License and of the GNU General Public License along with mmg (in
**  files COPYING.LESSER and COPYING). If not, see
**  <http://www.gnu.org/licenses/>. Please read their terms carefully and
**  use this copy of the mmg distribution only if you accept them.
** =============================================================================
*/

/**
 * \file mmg3d/libmmg3d.h
 * \brief C API for MMG3D library.
 * \author Algiane Froehly (Inria / IMB, Université de Bordeaux)
 * \version 5
 * \date 01 2014
 * \copyright GNU Lesser General Public License.
 *
 * \include mmg3d/example0/example0_a/main.c
 * \include mmg3d/example0/example0_b/main.c
 * \include mmg3d/example0_fortran/example0_a/main.F90
 * \include mmg3d/example0_fortran/example0_b/main.F90
 * \include mmg3d/example1/main.c
 * \include mmg3d/example2/main.c
 * \include mmg3d/example3/mmg3d.c
 * \include mmg3d/example4/main.c
 */

#ifndef _MMG3DLIB_H
#define _MMG3DLIB_H

#include "mmg.h"

/**
 * \def MMG5_SUCCESS
 *
 * Return value for success.
 *
 */
#define MMG5_SUCCESS       0
/**
 * \def MMG5_LOWFAILURE
 *
 * Return value if the remesh process failed but we can save a conform
 * mesh.
 *
 */
#define MMG5_LOWFAILURE    1
/**
 * \def MMG5_STRONGFAILURE
 *
 * Return value if the remesh process failed and the mesh is
 * non-conform.
 *
 */
#define MMG5_STRONGFAILURE 2

/**
 * \enum MMG5_type
 * \brief Type of solutions.
 */
enum MMG5_type
{
  MMG5_Notype, /*!< Undefined type (unusable) */
  MMG5_Scalar, /*!< Scalar solution */
  MMG5_Vector, /*!< Vectorial solution */
  MMG5_Tensor  /*!< Tensorial solution */
};

/**
 * \enum MMG5_entities
 * \brief Type of mesh entities to which solutions are applied.
 */
enum MMG5_entities
{
  MMG5_Noentity, /*!< Undefined type (unusable) */
  MMG5_Vertex, /*!< Vertex entity */
  MMG5_Triangle, /*!< Triangle entity */
};

/**
 * \enum MMG5_Param
 * \brief Input parameters for mmg library.
 *
 * Input parameters for mmg library. Options prefixed by \a
 * MMG5_IPARAM asked for integers values ans options prefixed by \a
 * MMG5_DPARAM asked for real values.
 *
 */
enum MMG5_Param
{
  MMG5_IPARAM_verbose,           /*!< [-10..10], Tune level of verbosity */
  MMG5_IPARAM_mem,               /*!< [n/-1], Set memory size to n Mbytes or keep the default value */
  MMG5_IPARAM_debug,             /*!< [1/0], Turn on/off debug mode */
  MMG5_IPARAM_angle,             /*!< [1/0], Turn on/off angle detection */
  MMG5_IPARAM_iso,               /*!< [1/0], Level-set meshing */
  MMG5_IPARAM_lag,               /*!< [-1/0/1/2], Lagrangian option */
  MMG5_IPARAM_optim,             /*!< [1/0], Optimize mesh keeping its initial edge sizes */
  MMG5_IPARAM_noinsert,          /*!< [1/0], Avoid/allow point insertion */
  MMG5_IPARAM_noswap,            /*!< [1/0], Avoid/allow edge or face flipping */
  MMG5_IPARAM_nomove,            /*!< [1/0], Avoid/allow point relocation */
  MMG5_IPARAM_nosurf,            /*!< [1/0], Avoid/allow surface modifications */
  MMG5_IPARAM_numberOfLocalParam,/*!< [n], Number of local parameters */
  MMG5_IPARAM_renum,             /*!< [1/0], Turn on/off point relocation with Scotch */
  MMG5_IPARAM_bucket,            /*!< [n], Specify the size of the bucket per dimension (DELAUNAY) */
  MMG5_DPARAM_angleDetection,    /*!< [val], Value for angle detection */
  MMG5_DPARAM_hmin,              /*!< [val], Minimal mesh size */
  MMG5_DPARAM_hmax,              /*!< [val], Maximal mesh size */
  MMG5_DPARAM_hausd,             /*!< [val], Control global Hausdorff distance (on all the boundary surfaces of the mesh) */
  MMG5_DPARAM_hgrad,             /*!< [val], Control gradation */
  MMG5_DPARAM_ls,                /*!< [val], Value of level-set (not use for now) */
  MMG5_PARAM_size,               /*!< [n], Number of parameters */
};


/*----------------------------- functions header -----------------------------*/
/* Initialization functions */
/* init structures */
/**
 * \param mesh adress of a pointer toward a pointer toward the mesh structure.
 * \param sol adress of a pointer toward a sol structure (metric or level-set).
 * \param disp adress of a pointer toward a sol structure
 * (displacement for the lagrangian mode).
 *
 * Allocate the mesh and solution structures and initialize it to
 * their default values.
 *
 */
void  MMG5_Init_mesh(MMG5_pMesh *mesh, MMG5_pSol *sol, MMG5_pSol *disp );
/* init structure sizes */
/**
 * \param mesh pointer toward the mesh structure.
 * \param sol pointer toward the sol structure.
 * \param typEntity type of solutions entities (vertices, triangles...).
 * \param np number of solutions.
 * \param typSol type of solution (scalar, vectorial...).
 * \return 0 if failed, 1 otherwise.
 *
 * Set the solution number, dimension and type.
 *
 */
int  MMG5_Set_solSize(MMG5_pMesh mesh, MMG5_pSol sol, int typEntity, int np, int typSol);
/**
 * \param mesh pointer toward the mesh structure.
 * \param np number of vertices.
 * \param ne number of elements (tetrahedra).
 * \param nt number of triangles.
 * \param na number of edges.
 * \return 0 if failed, 1 otherwise.
 *
 * Set the number of vertices, tetrahedra, triangles and edges of the
 * mesh and allocate the associated tables. If call twice, reset the
 * whole mesh to realloc it at the new size
 *
 */
int  MMG5_Set_meshSize(MMG5_pMesh mesh, int np, int ne, int nt, int na);

/* init structure datas */
/**
 * \param mesh pointer toward the mesh structure.
 * \param c0 coordinate of the point along the first dimension.
 * \param c1 coordinate of the point along the second dimension.
 * \param c2 coordinate of the point along the third dimension.
 * \param ref point reference.
 * \param pos position of the point in the mesh.
 * \return 1.
 *
 * Set vertex of coordinates \a c0, \a c1,\a c2 and reference \a ref
 * at position \a pos in mesh structure
 *
 */
int  MMG5_Set_vertex(MMG5_pMesh mesh, double c0, double c1,
                     double c2, int ref,int pos);
/**
 * \param mesh pointer toward the mesh structure.
 * \param v0 first vertex of tetrahedron.
 * \param v1 second vertex of tetrahedron.
 * \param v2 third vertex of tetrahedron.
 * \param v3 fourth vertex of tetrahedron.
 * \param ref tetrahedron reference.
 * \param pos tetrahedron position in the mesh.
 * \return 0 if failed, 1 otherwise.
 *
 * Set tetrahedra of vertices \a v0, \a v1,\a v2,\a v3 and reference
 * \a ref at position \a pos in mesh structure.
 *
 */
int  MMG5_Set_tetrahedron(MMG5_pMesh mesh, int v0, int v1,
                          int v2, int v3, int ref, int pos);
/**
 * \param mesh pointer toward the mesh structure.
 * \param v0 first vertex of triangle.
 * \param v1 second vertex of triangle.
 * \param v2 third vertex of triangle.
 * \param ref triangle reference.
 * \param pos triangle position in the mesh.
 * \return 0 if failed, 1 otherwise.
 *
 * Set triangle of vertices \a v0, \a v1, \a v2 and reference \a ref
 * at position \a pos in mesh structure.
 *
 */
int  MMG5_Set_triangle(MMG5_pMesh mesh, int v0, int v1,
                       int v2, int ref,int pos);
/**
 * \param mesh pointer toward the mesh structure.
 * \param v0 first extremity of the edge.
 * \param v1 second extremity of the edge.
 * \param ref edge reference.
 * \param pos edge position in the mesh.
 * \return 0 if failed, 1 otherwise.
 *
 * Set edges of extremities \a v0, \a v1 and reference \a ref at
 * position \a pos in mesh structure
 *
 */
int  MMG5_Set_edge(MMG5_pMesh mesh, int v0, int v1, int ref,int pos);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k vertex index.
 * \return 1.
 *
 * Set corner at point \a pos.
 *
 */
int  MMG5_Set_corner(MMG5_pMesh mesh, int k);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k vertex index.
 * \return 1.
 *
 * Set point \a k as required.
 *
 */
int  MMG5_Set_requiredVertex(MMG5_pMesh mesh, int k);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k element index.
 * \return 1.
 *
 * Set element \a k as required.
 *
 */
int  MMG5_Set_requiredTetrahedron(MMG5_pMesh mesh, int k);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k triangle index.
 * \return 1.
 *
 * Set triangle \a k as required.
 *
 */
int  MMG5_Set_requiredTriangle(MMG5_pMesh mesh, int k);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k edge index.
 * \return 1.
 *
 * Set ridge at edge \a k.
 *
 */
int  MMG5_Set_ridge(MMG5_pMesh mesh, int k);
/**
 * \param mesh pointer toward the mesh structure.
 * \param k edge index.
 * \return 1.
 *
 * Set edge \a k as required.
 *
 */
int  MMG5_Set_requiredEdge(MMG5_pMesh mesh, int k);
/**
 * \param met pointer toward the sol structure.
 * \param s solution scalar value.
 * \param pos position of the solution in the mesh.
 * \return 0 if failed, 1 otherwise.
 *
 * Set scalar value \a s at position \a pos in solution structure
 *
 */
int  MMG5_Set_scalarSol(MMG5_pSol met, double s,int pos);
/**
 * \param met pointer toward the sol structure.
 * \param vx x value of the vectorial solution.
 * \param vy y value of the vectorial solution.
 * \param vz z value of the vectorial solution.
 * \param pos position of the solution in the mesh (begin to 1).
 * \return 0 if failed, 1 otherwise.
 *
 * Set vectorial value \f$(v_x,v_y,v_z)\f$ at position \a pos in solution
 * structure.
 *
 */
int MMG5_Set_vectorSol(MMG5_pSol met, double vx,double vy, double vz, int pos);
/**
 * \param met pointer toward the sol structure.
 * \param m11 value of the tensorial solution at position (1,1) in the tensor.
 * \param m12 value of the tensorial solution at position (1,2) in the tensor.
 * \param m13 value of the tensorial solution at position (1,3) in the tensor.
 * \param m22 value of the tensorial solution at position (2,2) in the tensor.
 * \param m23 value of the tensorial solution at position (2,3) in the tensor.
 * \param m33 value of the tensorial solution at position (3,3) in the tensor.
 * \param pos position of the solution in the mesh (begin to 1).
 * \return 0 if failed, 1 otherwise.
 *
 * Set tensorial values at position \a pos in solution
 * structure.
 *
 */
int MMG5_Set_tensorSol(MMG5_pSol met, double m11,double m12, double m13,
                       double m22,double m23, double m33, int pos);
/**
 * \param mesh pointer toward the mesh structure.
 *
 * To mark as ended a mesh given without using the API functions
 * (for example, mesh given by mesh->point[i] = 0 ...). Not recommanded.
 *
 */
void MMG5_Set_handGivenMesh(MMG5_pMesh mesh);

/* check init */
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \return 0 if failed, 1 otherwise.
 *
 * Check if the number of given entities match with mesh and sol size
 * (not mandatory) and check mesh datas.
 *
 */
int MMG5_Chk_meshData(MMG5_pMesh mesh, MMG5_pSol met);

/** functions to set parameters */
/**
 * \param mesh pointer toward the mesh structure.
 * \param sol pointer toward the sol structure.
 * \param iparam integer parameter to set (see \a MMG5_Param structure).
 * \param val value for the parameter.
 * \return 0 if failed, 1 otherwise.
 *
 * Set integer parameter \a iparam at value \a val.
 *
 */
int  MMG5_Set_iparameter(MMG5_pMesh mesh,MMG5_pSol sol, int iparam, int val);
/**
 * \param mesh pointer toward the mesh structure.
 * \param sol pointer toward the sol structure.
 * \param dparam double parameter to set (see \a MMG5_Param structure).
 * \param val value of the parameter.
 * \return 0 if failed, 1 otherwise.
 *
 * Set double parameter \a dparam at value \a val.
 *
 */
int  MMG5_Set_dparameter(MMG5_pMesh mesh,MMG5_pSol sol, int dparam, double val);
/**
 * \param mesh pointer toward the mesh structure.
 * \param sol pointer toward the sol structure.
 * \param typ type of entity (triangle, edge,...).
 * \param ref reference of the entity.
 * \param val value of the Hausdorff number.
 * \return 0 if failed, 1 otherwise.
 *
 * Set local parameters: set the hausdorff value at \a val for all
 * elements of type \a typ and reference \a ref.
 *
 */
int  MMG5_Set_localParameter(MMG5_pMesh mesh, MMG5_pSol sol, int typ, int ref, double val);

/** recover datas */
/**
 * \param mesh pointer toward the mesh structure.
 * \param np pointer toward the number of vertices.
 * \param ne pointer toward the number of elements (tetrahedra).
 * \param nt pointer toward the number of triangles.
 * \param na pointer toward the number of edges.
 * \return 1.
 *
 * Get the number of vertices, tetrahedra, triangles and edges of the mesh.
 *
 */
int  MMG5_Get_meshSize(MMG5_pMesh mesh, int* np, int* ne, int* nt, int* na);
/**
 * \param mesh pointer toward the mesh structure.
 * \param sol pointer toward the sol structure.
 * \param typEntity pointer toward the type of entities to which solutions are applied.
 * \param np pointer toward the number of solutions.
 * \param typSol pointer toward the type of the solutions (scalar, vectorial...)
 * \return 1.
 *
 * Get the solution number, dimension and type.
 *
 */
int  MMG5_Get_solSize(MMG5_pMesh mesh, MMG5_pSol sol, int* typEntity, int* np,
                      int* typSol);
/**
 * \param mesh pointer toward the mesh structure.
 * \param c0 pointer toward the coordinate of the point along the first dimension.
 * \param c1 pointer toward the coordinate of the point along the second dimension.
 * \param c2 pointer toward the coordinate of the point along the third dimension.
 * \param ref pointer to the point reference.
 * \param isCorner pointer toward the flag saying if point is corner.
 * \param isRequired pointer toward the flag saying if point is required.
 * \return 1.
 *
 * Get coordinates \a c0, \a c1,\a c2 and reference \a ref of next
 * vertex of mesh.
 *
 */
int  MMG5_Get_vertex(MMG5_pMesh mesh, double* c0, double* c1, double* c2, int* ref,
                     int* isCorner, int* isRequired);
/**
 * \param mesh pointer toward the mesh structure.
 * \param v0 pointer toward the first vertex of tetrahedron.
 * \param v1 pointer toward the second vertex of tetrahedron.
 * \param v2 pointer toward the third vertex of tetrahedron.
 * \param v3 pointer toward the fourth vertex of tetrahedron.
 * \param ref pointer toward the tetrahedron reference.
 * \param isRequired pointer toward the flag saying if tetrahedron is required.
 * \return 0 if failed, 1 otherwise.
 *
 * Get vertices \a v0, \a v1, \a v2, \a v3 and reference \a ref of
 * next tetra of mesh.
 *
 */
int  MMG5_Get_tetrahedron(MMG5_pMesh mesh, int* v0, int* v1, int* v2, int* v3,
                          int* ref, int* isRequired);
/**
 * \param mesh pointer toward the mesh structure.
 * \param v0 pointer toward the first vertex of triangle.
 * \param v1 pointer toward the second vertex of triangle.
 * \param v2 pointer toward the third vertex of triangle.
 * \param ref pointer toward the triangle reference.
 * \param isRequired pointer toward the flag saying if triangle is required.
 * \return 0 if failed, 1 otherwise.
 *
 * Get vertices \a v0,\a v1,\a v2 and reference \a ref of next
 * triangle of mesh.
 *
 */
int  MMG5_Get_triangle(MMG5_pMesh mesh, int* v0, int* v1, int* v2, int* ref,
                       int* isRequired);
/**
 * \param mesh pointer toward the mesh structure.
 * \param e0 pointer toward the first extremity of the edge.
 * \param e1 pointer toward the second  extremity of the edge.
 * \param ref pointer toward the edge reference.
 * \param isRidge pointer toward the flag saying if the edge is ridge.
 * \param isRequired pointer toward the flag saying if the edge is required.
 * \return 0 if failed, 1 otherwise.
 *
 * Get extremities \a e0, \a e1 and reference \a ref of next edge of mesh.
 *
 */
int  MMG5_Get_edge(MMG5_pMesh mesh, int* e0, int* e1, int* ref,
                   int* isRidge, int* isRequired);
/**
 * \param met pointer toward the sol structure.
 * \param s pointer toward the scalar solution value.
 * \return 0 if failed, 1 otherwise.
 *
 * Get solution \a s of next vertex of mesh.
 *
 */
int  MMG5_Get_scalarSol(MMG5_pSol met, double* s);
/**
 * \param met pointer toward the sol structure.
 * \param vx x value of the vectorial solution.
 * \param vy y value of the vectorial solution.
 * \param vz z value of the vectorial solution.
 * \return 0 if failed, 1 otherwise.
 *
 * Get vectorial solution \f$(v_x,v_y,vz)\f$ of next vertex of mesh.
 *
 */
int MMG5_Get_vectorSol(MMG5_pSol met, double* vx, double* vy, double* vz);
/**
 * \param met pointer toward the sol structure.
 * \param m11 pointer toward the position (1,1) in the solution tensor.
 * \param m12 pointer toward the position (1,2) in the solution tensor.
 * \param m13 pointer toward the position (1,3) in the solution tensor.
 * \param m22 pointer toward the position (2,2) in the solution tensor.
 * \param m23 pointer toward the position (2,3) in the solution tensor.
 * \param m33 pointer toward the position (3,3) in the solution tensor.
 * \return 0 if failed, 1 otherwise.
 *
 * Get tensorial solution of next vertex of mesh.
 *
 */
int MMG5_Get_tensorSol(MMG5_pSol met, double *m11,double *m12, double *m13,
                       double *m22,double *m23, double *m33);
/**
 * \param mesh pointer toward the mesh structure.
 * \param iparam integer parameter to set (see \a MMG5_Param structure).
 * \return The value of integer parameter.
 *
 * Get the value of integer parameter \a iparam.
 *
 */
int MMG5_Get_iparameter(MMG5_pMesh mesh, int iparam);

/* input/output functions */
/**
 * \param mesh pointer toward the mesh structure.
 * \return 0 if failed, 1 otherwise.
 *
 * Read mesh data.
 *
 */
int  MMG5_loadMesh(MMG5_pMesh mesh);
/**
 * \param mesh pointer toward the mesh structure.
 * \return 0 if failed, 1 otherwise.
 *
 * Save mesh data.
 *
 */
int  MMG5_saveMesh(MMG5_pMesh mesh);
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \return 0 if failed, 1 otherwise.
 *
 * Load metric field.
 *
 */
int  MMG5_loadMet(MMG5_pMesh mesh,MMG5_pSol met);
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \return 0 if failed, 1 otherwise.
 *
 * Write isotropic or anisotropic metric.
 *
 */
int  MMG5_saveMet(MMG5_pMesh mesh, MMG5_pSol met);

/* deallocations */
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure (metric or solution).
 * \param disp pointer toward a sol structure (displacement for the
 * lagrangian mode).
 *
 * Deallocations before return.
 *
 */
void MMG5_Free_all(MMG5_pMesh mesh, MMG5_pSol met, MMG5_pSol disp );

/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure (metric or solution).
 * \param disp pointer toward a sol structure (displacement).
 *
 * Structure deallocations before return.
 *
 */
void MMG5_Free_structures(MMG5_pMesh mesh, MMG5_pSol met, MMG5_pSol disp );

/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward a sol structure (metric or solution).
 * \param disp pointer toward a sol structure (displacement).
 *
 * File name deallocations before return.
 *
 */
void MMG5_Free_names(MMG5_pMesh mesh, MMG5_pSol met, MMG5_pSol disp);

/* library */
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol (metric or level-set) structure.
 * \param disp pointer toward a sol (displacement for the lagrangian motion
 * mode) structure.
 * \return \ref MMG5_SUCCESS if success, \ref MMG5_LOWFAILURE if fail but a
 * conform mesh is saved or \ref MMG5_STRONGFAILURE if fail and we can't save
 * the mesh.
 *
 * Main program for the library.
 *
 */
int  MMG5_mmg3dlib(MMG5_pMesh mesh, MMG5_pSol met, MMG5_pSol disp );

/* for PAMPA library */
/** Options management */
/**
 * \param argc number of command line arguments.
 * \param argv command line arguments.
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \return 1.
 * \note Developped for the PaMPA library interface.
 *
 * Store command line arguments.
 *
 */
int  MMG5_parsar(int argc,char *argv[],MMG5_pMesh mesh,MMG5_pSol met);
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \return 1.
 * \note Developped for the PaMPA library interface.
 *
 * Read local parameters file. This file must have the same name as
 * the mesh with the \a .mmg3d5 extension or must be named \a
 * DEFAULT.mmg3d5.
 *
 */
int  MMG5_parsop(MMG5_pMesh mesh,MMG5_pSol met);
/**
 * \param prog pointer toward the program name.
 * \note Developped for the PaMPA library interface.
 *
 * Print help for mmg3d5 options.
 *
 */
void  MMG5_usage(char *prog);
/**
 * \param mesh pointer toward the mesh structure.
 * \param info pointer toward the info structure.
 * \return 1.
 * \note Developped for the PaMPA library interface.
 *
 * Store the info structure in the mesh structure.
 *
 */
int  MMG5_stockOptions(MMG5_pMesh mesh, MMG5_Info *info);
/**
 * \param mesh pointer toward the mesh structure.
 * \param info pointer toward the info structure.
 * \note Developped for the PaMPA library interface.
 *
 * Recover the info structure stored in the mesh structure.
 *
 */
void  MMG5_destockOptions(MMG5_pMesh mesh, MMG5_Info *info);

/** Checks */
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \param critmin minimum quality for elements.
 * \param lmin minimum edge length.
 * \param lmax maximum ede length.
 * \param eltab table of invalid elements.
 * \note Developped for the PaMPA library interface.
 *
 * Search invalid elements (in term of quality or edge length).
 *
 */
int MMG5_mmg3dcheck(MMG5_pMesh mesh,MMG5_pSol met,
                    double critmin, double lmin, double lmax, int *eltab);
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \param critmin minimum quality for elements.
 * \param eltab pointer toward the table of invalid elements.
 * \note Developped for the PaMPA library interface.
 *
 * Store elements which have worse quality than \a critmin in \a eltab,
 * \a eltab is allocated and could contain \a mesh->ne elements.
 *
 */
void  MMG5_searchqua(MMG5_pMesh mesh, MMG5_pSol met, double critmin, int *eltab);
/**
 * \param mesh pointer toward the mesh structure.
 * \param met pointer toward the sol structure.
 * \param lmin minimum edge length.
 * \param lmax maximum ede length.
 * \param eltab table of invalid elements.
 * \note Developped for the PaMPA library interface.
 *
 * Store in \a eltab elements which have edge lengths shorter than \a lmin
 * or longer than \a lmax, \a eltab is allocated and could contain \a mesh->ne
 * elements.
 *
 */
int  MMG5_searchlen(MMG5_pMesh mesh, MMG5_pSol met, double lmin, double lmax, int *eltab);

/** Utils */
/**
 * \brief Return adjacent elements of a tetrahedron.
 * \param mesh pointer toward the mesh structure.
 * \param kel tetrahedron index.
 * \param v0 pointer toward the index of the adjacent element of \a kel through
 * its face number 0.
 * \param v1 pointer toward the index of the adjacent element of \a kel through
 * its face number 1.
 * \param v2 pointer toward the index of the adjacent element of \a kel through
 * its face number 2.
 * \param v3 pointer toward the index of the adjacent element of \a kel through
 * its face number 3.
 * \return 1.
 * \note Developped for the PaMPA library interface.
 *
 * Find the indices of the 4 adjacent elements of tetrahedron \a
 * kel. \f$v_i = 0\f$ if the \f$i^{th}\f$ face has no adjacent element
 * (so we are on a boundary face).
 *
 */
int MMG5_Get_adjaTet(MMG5_pMesh mesh,int kel, int* v0, int* v1, int* v2, int* v3);
/**
 * \param ca pointer toward the coordinates of the first edge's extremity.
 * \param cb pointer toward the coordinates of the second edge's extremity.
 * \param ma pointer toward the metric associated to the first edge's extremity.
 * \param mb pointer toward the metric associated to the second edge's extremity.
 * \return edge length.
 * \note Developped for the PaMPA library interface.
 *
 * Compute length of edge \f$[ca,cb]\f$ (with \a ca and \a cb
 * coordinates of edge extremities) according to the size
 * prescription.
 *
 */
double (*MMG5_lenedgCoor)(double *ca,double *cb,double *sa,double *sb);
/**
 * \param mesh pointer toward the mesh structure.
 * \param pack we pack the mesh at function begining if \f$pack=1\f$.
 * \return 0 if failed, 1 otherwise.
 *
 * Create table of adjacency. Set pack variable to 0 for a compact
 * mesh and to 1 for a mesh that need to be packed.
 *
 */
int  (*MMG5_hashTetra)(MMG5_pMesh mesh, int pack);

/** To associate function pointers without calling MMG5_mmg3dlib */
/**
 * \param mesh pointer toward the mesh structure (unused).
 * \note Developped for the PaMPA library interface.
 *
 * Set pointer for MMG5_saveMesh function.
 *
 */
void  MMG5_Set_saveFunc(MMG5_pMesh mesh);
/**
 * \param mesh pointer toward the mesh structure (unused).
 * \param met pointer toward the sol structure (unused).
 * \note Developped for the PaMPA library interface.
 *
 * Set function pointers for caltet, lenedg, defsiz and gradsiz.
 *
 */
void  MMG5_setfunc(MMG5_pMesh mesh,MMG5_pSol met);
/**
 * \param mesh pointer toward the mesh structure (unused).
 * \param met pointer toward the sol structure (unused).
 * \warning Copy of the \a setfunc function of the \a mmg3d/shared_func.h
 * file.
 * \note Developped for the PaMPA library interface.
 *
 * Set function pointers for lenedgeCoor, hashTetra and saveMesh.
 *
 */
void  MMG5_pampa_setfunc(MMG5_pMesh mesh,MMG5_pSol met);

#endif
