#ifndef _LINEARKERNEL_H___
#define _LINEARKERNEL_H___

#include "lib/common.h"
#include "kernel/RealKernel.h"
#include "features/RealFeatures.h"

class CLinearKernel: public CRealKernel
{
 public:
  CLinearKernel(LONG size, bool do_rescale=true, REAL scale=1.0);
  virtual ~CLinearKernel();
  
  virtual bool init(CFeatures* l, CFeatures* r, bool do_init);
  virtual void cleanup();

  /// load and save kernel init_data
  virtual bool load_init(FILE* src);
  virtual bool save_init(FILE* dest);

  // return what type of kernel we are Linear,Polynomial, Gaussian,...
  virtual EKernelType get_kernel_type() { return K_LINEAR; }

  // return the name of a kernel
  virtual const CHAR* get_name() { return "Linear" ; } ;

  ///optimizable kernel, i.e. precompute normal vector and as phi(x)=x
  ///do scalar product in input space
  virtual bool init_optimization(INT num_suppvec, INT* sv_idx, REAL* alphas);
  virtual bool delete_optimization();
  virtual REAL compute_optimized(INT idx);

  virtual void clear_normal();
  virtual void add_to_normal(INT idx, REAL weight);

  inline const double* get_normal(INT& len)
  {

	  if (lhs && normal)
	  {
		  len = ((CRealFeatures*) lhs)->get_num_features();
		  return normal;
	  }
	  else
	  {
		  len = 0;
		  return NULL;
	  }
  }

 protected:
  /// compute kernel function for features a and b
  /// idx_{a,b} denote the index of the feature vectors
  /// in the corresponding feature object
  virtual REAL compute(INT idx_a, INT idx_b);
  /*    compute_kernel*/

  virtual void init_rescale();
  
 protected:
  double scale ;
  bool do_rescale ;

  /// normal vector (used in case of optimized kernel)
  double* normal;
};
#endif
