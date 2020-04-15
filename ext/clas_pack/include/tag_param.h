
/*--------------*
 * tagcal_param.h *
   image of common/tagparam/ 
 *--------------*/
/* -=======================================================- *
$Id: tag_param.h,v 1.2 2006/03/13 23:25:19 pasyuk Exp $
* -=======================================================- */


typedef struct {
  double adj_T_coinc;
  double adj_E_coinc;
  double ET_window;
  double E_tdc_min;
  double E_tdc_max;
  double TAG_DSD_window;
  double TAG_ST_window;
  double TAG_DSD_Xtrawindow;
  double TAG_ST_Xtrawindow;
  double PS_coinc_window;
  double TLR_window;
} TagParam_t;

extern TagParam_t tagparam_;
