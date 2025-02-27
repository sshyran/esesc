/*****************************************************************************
 *                                McPAT
 *                      SOFTWARE LICENSE AGREEMENT
 *            Copyright 2009 Hewlett-Packard Development Company, L.P.
 *                          All Rights Reserved
 *
 * Permission to use, copy, and modify this software and its documentation is
 * hereby granted only under the following terms and conditions.  Both the
 * above copyright notice and this permission notice must appear in all copies
 * of the software, derivative works or modified versions, and any portions
 * thereof, and both notices must appear in supporting documentation.
 *
 * Any User of the software ("User"), by accessing and using it, agrees to the
 * terms and conditions set forth herein, and hereby grants back to Hewlett-
 * Packard Development Company, L.P. and its affiliated companies ("HP") a
 * non-exclusive, unrestricted, royalty-free right and license to copy,
 * modify, distribute copies, create derivate works and publicly display and
 * use, any changes, modifications, enhancements or extensions made to the
 * software by User, including but not limited to those affording
 * compatibility with other hardware or software, but excluding pre-existing
 * software applications that may incorporate the software.  User further
 * agrees to use its best efforts to inform HP of any such changes,
 * modifications, enhancements or extensions.
 *
 * Correspondence should be provided to HP at:
 *
 * Director of Intellectual Property Licensing
 * Office of Strategy and Technology
 * Hewlett-Packard Company
 * 1501 Page Mill Road
 * Palo Alto, California  94304
 *
 * The software may be further distributed by User (but not offered for
 * sale or transferred for compensation) to third parties, under the
 * condition that such third parties agree to abide by the terms and
 * conditions of this license.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" WITH ANY AND ALL ERRORS AND DEFECTS
 * AND USER ACKNOWLEDGES THAT THE SOFTWARE MAY CONTAIN ERRORS AND DEFECTS.
 * HP DISCLAIMS ALL WARRANTIES WITH REGARD TO THE SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.   IN NO EVENT SHALL
 * HP BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES
 * OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
 * WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER ACTION, ARISING
 * OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THE SOFTWARE.
 *
 ***************************************************************************/

#ifndef __MAT_H__
#define __MAT_H__

#include "component.h"
#include "decoder.h"
#include "subarray.h"
#include "wire.h"

class Mat : public Component {
public:
  Mat(const DynamicParameter &dyn_p);
  ~Mat();
  double compute_delays(double inrisetime); // return outrisetime
  void   compute_power_energy();

  const DynamicParameter &dp;

  // TODO: clean up pointers and powerDefs below
  Decoder *     row_dec;
  Decoder *     bit_mux_dec;
  Decoder *     sa_mux_lev_1_dec;
  Decoder *     sa_mux_lev_2_dec;
  PredecBlk *   dummy_way_sel_predec_blk1;
  PredecBlk *   dummy_way_sel_predec_blk2;
  PredecBlkDrv *way_sel_drv1;
  PredecBlkDrv *dummy_way_sel_predec_blk_drv2;

  Predec *r_predec;
  Predec *b_mux_predec;
  Predec *sa_mux_lev_1_predec;
  Predec *sa_mux_lev_2_predec;

  Wire *  subarray_out_wire;
  Driver *bl_precharge_eq_drv;
  Driver *cam_bl_precharge_eq_drv; // bitline pre-charge circuit is separated for CAM and RAM arrays.
  Driver *ml_precharge_drv;        // matchline prechange driver
  Driver *sl_precharge_eq_drv;     // searchline prechage driver
  Driver *sl_data_drv;             // search line data driver
  Driver *ml_to_ram_wl_drv;        // search line data driver

  powerDef power_row_decoders;
  powerDef power_bit_mux_decoders;
  powerDef power_sa_mux_lev_1_decoders;
  powerDef power_sa_mux_lev_2_decoders;
  powerDef power_fa_cam; // TODO: leakage power is not computed yet
  powerDef power_bl_precharge_eq_drv;
  powerDef power_subarray_out_drv;
  powerDef power_cam_all_active;
  powerDef power_searchline_precharge;
  powerDef power_matchline_precharge;
  powerDef power_ml_to_ram_wl_drv;

  double delay_fa_tag, delay_cam;
  double delay_before_decoder;
  double delay_bitline;
  double delay_wl_reset;
  double delay_bl_restore;

  double delay_searchline;
  double delay_matchchline;
  double delay_cam_sl_restore;
  double delay_cam_ml_reset;
  double delay_fa_ram_wl;

  double delay_hit_miss_reset;
  double delay_hit_miss;

  Subarray subarray;
  powerDef power_bitline, power_searchline, power_matchline;
  double   per_bitline_read_energy;
  int      deg_bl_muxing;
  int      num_act_mats_hor_dir;
  double   delay_writeback;
  Area     cell, cam_cell;
  bool     is_dram, is_fa, pure_cam, camFlag;
  int      num_mats;
  powerDef power_sa;
  double   delay_sa;
  double   leak_power_sense_amps_closed_page_state;
  double   leak_power_sense_amps_open_page_state;
  double   delay_subarray_out_drv;
  double   delay_subarray_out_drv_htree;
  double   delay_comparator;
  powerDef power_comparator;
  int      num_do_b_mat;
  int      num_so_b_mat;
  int      num_sa_subarray;
  int      num_sa_subarray_search;
  double   C_bl;

  uint32_t num_subarrays_per_mat; // the number of subarrays in a mat
  uint32_t num_subarrays_per_row; // the number of subarrays in a row of a mat

private:
  double compute_bit_mux_sa_precharge_sa_mux_wr_drv_wr_mux_h();
  double width_write_driver_or_write_mux();
  double compute_comparators_height(int tagbits, int number_ways_in_mat, double subarray_mem_cell_area_w);
  double compute_cam_delay(double inrisetime);
  double compute_bitline_delay(double inrisetime);
  double compute_sa_delay(double inrisetime);
  double compute_subarray_out_drv(double inrisetime);
  double compute_comparator_delay(double inrisetime);

  int RWP;
  int ERP;
  int EWP;
  int SCHP;
};

#endif
