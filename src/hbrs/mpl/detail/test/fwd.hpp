/* Copyright (c) 2016-2019 Jakob Meng, <jakobmeng@web.de>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef HBRS_MPL_DETAIL_TEST_FWD_HPP
#define HBRS_MPL_DETAIL_TEST_FWD_HPP

#include <hbrs/mpl/config.hpp>

HBRS_MPL_NAMESPACE_BEGIN
namespace detail {

inline static constexpr std::size_t
mat_a_m = 3, mat_a_n = 3;

inline static constexpr double
mat_a[mat_a_m*mat_a_n] = {
	12.0, -51.0,   4.0,
	06.0, 167.0, -68.0,
	-4.0,  24.0, -41.0
};

inline static constexpr std::size_t
mat_b_m = 5, mat_b_n = 3;

inline static constexpr double
mat_b[mat_b_m*mat_b_n] = {
	12, -51,   4,
	06, 167, -68,
	-4,  24, -41,
	-1,   1,   0,
	02,   0,   3,
};


inline static constexpr std::size_t
mat_c_m = 6, mat_c_n = 5;

inline static constexpr double 
mat_c[mat_c_m*mat_c_n] = {
	+8.79,  +9.93,  +9.83, +5.45,  +3.16,
	+6.11,  +6.91,  +5.04, -0.27,  +7.98,
	-9.15,  -7.93,  +4.86, +4.85,  +3.01,
	+9.57,  +1.64,  +8.83, +0.74,  +5.80,
	-3.49,  +4.02,  +9.80, +10.00, +4.27,
	+9.84,  +0.15,  -8.99, -6.02,  -5.31
};

inline static constexpr std::size_t
mat_d_m = 2, mat_d_n = 2;

inline static constexpr double 
mat_d[mat_d_m*mat_d_n] = {
	00,  1,
	-2, -3
};

inline static constexpr std::size_t
mat_e_m = 3, mat_e_n = 5;

inline static constexpr double 
mat_e[mat_e_m*mat_e_n] = {
	1,0,0,0,2,
	0,0,3,0,0,
	0,2,0,0,0
};

inline static constexpr std::size_t
mat_f_m = 2, mat_f_n = 3;

inline static constexpr double
mat_f[mat_f_m*mat_f_n] = {
	1,2,3,
	-1,2,5
};

inline static constexpr std::size_t
mat_g_m = 13, mat_g_n = 4;

/* This is ingredients matrix from hald.mat used e.g. at https://de.mathworks.com/help/stats/pca.html
 * more sample data sets can be found at https://de.mathworks.com/help/stats/sample-data-sets.html 
 */
inline static constexpr double 
mat_g[mat_g_m*mat_g_n] = {
	07,   26,    6,   60,
	01,   29,   15,   52,
	11,   56,    8,   20,
	11,   31,    8,   47,
	07,   52,    6,   33,
	11,   55,    9,   22,
	03,   71,   17,    6,
	01,   31,   22,   44,
	02,   54,   18,   22,
	21,   47,    4,   26,
	01,   40,   23,   34,
	11,   66,    9,   12,
	10,   68,    8,   12
};

inline static constexpr std::size_t
mat_h_m = 3, mat_h_n = 4;

inline static constexpr double 
mat_h[mat_h_m*mat_h_n] = {
	11, 12, 13, 14,
	21, 22, 23, 24,
	31, 32, 33, 34
};

inline static constexpr std::size_t
mat_i_m = 3, mat_i_n = 4;

inline static constexpr double 
mat_i[mat_i_m*mat_i_n] = {
	11, 21, 31, 
	12, 22, 32,
	13, 23, 33,
	14, 24, 34
};

inline static constexpr std::size_t
mat_j_m = 4, mat_j_n = 13;

/* transpose of mat_g */
inline static constexpr double 
mat_j[mat_j_m*mat_j_n] = {
	07,  1, 11, 11,  7, 11,  3,  1,  2, 21,  1, 11, 10,
	26, 29, 56, 31, 52, 55, 71, 31, 54, 47, 40, 66, 68,
	06, 15,  8,  8,  6,  9, 17, 22, 18,  4, 23,  9,  8,
	60, 52, 20, 47, 33, 22,  6, 44, 22, 26, 34, 12, 12
};

inline static constexpr std::size_t
mat_k_m = 24, mat_k_n = 24;

inline static constexpr double 
mat_k[mat_k_m*mat_k_n] = {
	47, -14,   0, -47,  45,  14, -26, -18,  -8,  10,  27, -45, 10, -16,   8,   5,  -1, -15, -27, -24, -41,   2, -40,  39,
	38, -38, -28, -22, -35,  -1, -29,  -2,  15,  12,  38,  29, 42,  40, -44, -20,  -6,  44, -33,  -9, -24, -27, -24, -17,
	41,  -2,  43, -15,  13, -23, -33, -39,  24, -11,  47,  48, 26, -13, -27,  24,  -5,  38, -27,   9,  30,  -1, -16,  20,
	-1,  -9,  -1, -26, -14, -16,  16,  22, -33, -11, -32,  16, 38, -39, -15, -31, -19,   5,  -6, -24, -47,  12,  18, -30,
	49, -44, -12, -25, -42,  -8,  -3,   9,  25,  44, -19,   5, 32,  28,  32,  19,   1,  12, -19,  10,  43,  18, -36, -47,
	13,  44, -33,  14,  36, -28,  16,  28, -37, -14, -20,  16, 26, -11, -48, -32,   1,   9,  42,  21,  23, -10,  22,  24,
	13, -25,  42,  46, -16,   7,   0,  -7, -48,  18,  30,   7, -8, -26, -46, -13,  32, -29,  -7, -28,  -1, -13, -39,   0,
	31, -37, -37,   7,  39,  -7, -35, -34,  24,   1,   4, -33, 45, -10, -33,  13,  29, -20, -32, -38,   8,  49,  15,  -2,
	26,  32,  12,  -6, -28,   2,  -9,  39,  33,  10,  29, -48, 40, -40,  15,  28,  14,  -3,  40, -20, -26, -46,  -1,  40,
	30, -14,  47, -21, -44, -32, -49, -38,   9,  25, -27, -24, 44, -37,  23, -42, -12, -27,  48, -18,  -4,  39,  28,  11,
	39, -47, -26, -44, -27,  10, -40, -38,  -6,  10,  24,  48, -1,  44,  15,  43,  31,  34,  -6,  -8,  46,  41,  22,  12,
	20, -13,  14, -37, -47, -44,  49,  40, -36,   9,  25,  26, -1,  46,  -5,  28,   3, -31, -39,   1,   5,  30,  40,  36,
	31,  46,  18,  19,  21,  25,  31,  42,   7,  19, -39, -32, 31, -44,  47, -44, -13,  -8, -47, -31,  32,  -7, -43,  28,
	41,  -1,  26, -18,  25, -24, -26, -21,  -3,  25,  46, -24, -8,  18,  15, -10, -30,  48,   6,  -7,  48, -19, -18,  -8,
	37,  30,  24,  45, -22,   1,  43,  26, -49,  -5, -50, -35, 32, -46,  30,   3,  -1, -20,  38,  -2,  23, -34,   3, -41,
	41, -36, -11, -47,  18,  20, -15,  25, -16, -42,  27, -36, 26, -43,  -5,  -8, -16,  20,  17, -38, -16, -32,  15, -23,
	13,  -8,  16,  -6,  16,  39, -30, -12, -34, -27,  32,  37, 39,   2,  -7,  16,  45,  17, -31,   9,   8,  -8,  -9, -35,
	40,  42, -33, -12, -34,  46, -25,   7,  29,  41,  37,   8, 47, -40,  33,  13,  42,   4, -13, -27, -39, -41,  32, -22,
	22,  29,  21,  27, -38,   5,  12, -42, -19, -35, -42,   5, -1,  32, -42, -21, -45,  20,  -4, -12,  41,  10,  22,  -6,
	-5,  46, -47,  30,   0, -36,  -3, -45,   3,  33, -10, -36, 33,  32, -37,  -7,  24,  17,  48,   8,  38,  -3,  47,   3,
	46,  16, -22, -31,  46, -35, -15,   3, -33,   4, -24,  35, 48,  22, -33, -48, -23, -32, -34, -25,  32,  20,   3,  -4,
	46, -46, -45,  -1, -16, -24,  33,  28,  10,  50,  30,  12, 21, -35, -11,  48,  -8, -37,  36, -21, -24,  20, -17,  38,
	34,  35, -40,  -5,   9,  34,   9,  43, -24, -42,  -7, -15, -9,  16,  33, -33,   5,  50,  14,  12,   9,  14, -39,   2,
	47,  43,  32,  15, -28, -25,   5, -37,  15,  -6,  41,   1, -3,   2,  30, -39,  44, -33, -12, -23, -48, -47,  11,  44
};

inline static constexpr std::size_t
mat_l_m = 24, mat_l_n = 12;

inline static constexpr double 
mat_l[mat_l_m*mat_l_n] = {
	47, -14,   0, -47,  45,  14, -26, -18,  -8,  10,  27, -45,
	38, -38, -28, -22, -35,  -1, -29,  -2,  15,  12,  38,  29,
	41,  -2,  43, -15,  13, -23, -33, -39,  24, -11,  47,  48,
	-1,  -9,  -1, -26, -14, -16,  16,  22, -33, -11, -32,  16,
	49, -44, -12, -25, -42,  -8,  -3,   9,  25,  44, -19,   5,
	13,  44, -33,  14,  36, -28,  16,  28, -37, -14, -20,  16,
	13, -25,  42,  46, -16,   7,   0,  -7, -48,  18,  30,   7,
	31, -37, -37,   7,  39,  -7, -35, -34,  24,   1,   4, -33,
	26,  32,  12,  -6, -28,   2,  -9,  39,  33,  10,  29, -48,
	30, -14,  47, -21, -44, -32, -49, -38,   9,  25, -27, -24,
	39, -47, -26, -44, -27,  10, -40, -38,  -6,  10,  24,  48,
	20, -13,  14, -37, -47, -44,  49,  40, -36,   9,  25,  26,
	31,  46,  18,  19,  21,  25,  31,  42,   7,  19, -39, -32,
	41,  -1,  26, -18,  25, -24, -26, -21,  -3,  25,  46, -24,
	37,  30,  24,  45, -22,   1,  43,  26, -49,  -5, -50, -35,
	41, -36, -11, -47,  18,  20, -15,  25, -16, -42,  27, -36,
	13,  -8,  16,  -6,  16,  39, -30, -12, -34, -27,  32,  37,
	40,  42, -33, -12, -34,  46, -25,   7,  29,  41,  37,   8,
	22,  29,  21,  27, -38,   5,  12, -42, -19, -35, -42,   5,
	-5,  46, -47,  30,   0, -36,  -3, -45,   3,  33, -10, -36,
	46,  16, -22, -31,  46, -35, -15,   3, -33,   4, -24,  35,
	46, -46, -45,  -1, -16, -24,  33,  28,  10,  50,  30,  12,
	34,  35, -40,  -5,   9,  34,   9,  43, -24, -42,  -7, -15,
	47,  43,  32,  15, -28, -25,   5, -37,  15,  -6,  41,   1
};

inline static constexpr std::size_t
mat_m_m = 12, mat_m_n = 24;

inline static constexpr double 
mat_m[mat_m_m*mat_m_n] = {
	47, -14,   0, -47,  45,  14, -26, -18,  -8,  10,  27, -45, 10, -16,   8,   5,  -1, -15, -27, -24, -41,   2, -40,  39,
	38, -38, -28, -22, -35,  -1, -29,  -2,  15,  12,  38,  29, 42,  40, -44, -20,  -6,  44, -33,  -9, -24, -27, -24, -17,
	41,  -2,  43, -15,  13, -23, -33, -39,  24, -11,  47,  48, 26, -13, -27,  24,  -5,  38, -27,   9,  30,  -1, -16,  20,
	-1,  -9,  -1, -26, -14, -16,  16,  22, -33, -11, -32,  16, 38, -39, -15, -31, -19,   5,  -6, -24, -47,  12,  18, -30,
	49, -44, -12, -25, -42,  -8,  -3,   9,  25,  44, -19,   5, 32,  28,  32,  19,   1,  12, -19,  10,  43,  18, -36, -47,
	13,  44, -33,  14,  36, -28,  16,  28, -37, -14, -20,  16, 26, -11, -48, -32,   1,   9,  42,  21,  23, -10,  22,  24,
	13, -25,  42,  46, -16,   7,   0,  -7, -48,  18,  30,   7, -8, -26, -46, -13,  32, -29,  -7, -28,  -1, -13, -39,   0,
	31, -37, -37,   7,  39,  -7, -35, -34,  24,   1,   4, -33, 45, -10, -33,  13,  29, -20, -32, -38,   8,  49,  15,  -2,
	26,  32,  12,  -6, -28,   2,  -9,  39,  33,  10,  29, -48, 40, -40,  15,  28,  14,  -3,  40, -20, -26, -46,  -1,  40,
	30, -14,  47, -21, -44, -32, -49, -38,   9,  25, -27, -24, 44, -37,  23, -42, -12, -27,  48, -18,  -4,  39,  28,  11,
	39, -47, -26, -44, -27,  10, -40, -38,  -6,  10,  24,  48, -1,  44,  15,  43,  31,  34,  -6,  -8,  46,  41,  22,  12,
	20, -13,  14, -37, -47, -44,  49,  40, -36,   9,  25,  26, -1,  46,  -5,  28,   3, -31, -39,   1,   5,  30,  40,  36
};

inline static constexpr std::size_t
mat_n_m = 12, mat_n_n = 24;

/* transpose of mat_l */
inline static constexpr double 
mat_n[mat_n_m*mat_n_n] = {
	 47, 38, 41, -1, 49, 13, 13, 31, 26, 30, 39, 20, 31, 41, 37, 41, 13, 40, 22, -5, 46, 46, 34, 47,
	-14,-38, -2, -9,-44, 44,-25,-37, 32,-14,-47,-13, 46, -1, 30,-36, -8, 42, 29, 46, 16,-46, 35, 43,
	  0,-28, 43, -1,-12,-33, 42,-37, 12, 47,-26, 14, 18, 26, 24,-11, 16,-33, 21,-47,-22,-45,-40, 32,
	-47,-22,-15,-26,-25, 14, 46,  7, -6,-21,-44,-37, 19,-18, 45,-47, -6,-12, 27, 30,-31, -1, -5, 15,
	 45,-35, 13,-14,-42, 36,-16, 39,-28,-44,-27,-47, 21, 25,-22, 18, 16,-34,-38,  0, 46,-16,  9,-28,
	 14, -1,-23,-16, -8,-28,  7, -7,  2,-32, 10,-44, 25,-24,  1, 20, 39, 46,  5,-36,-35,-24, 34,-25,
	-26,-29,-33, 16, -3, 16,  0,-35, -9,-49,-40, 49, 31,-26, 43,-15,-30,-25, 12, -3,-15, 33,  9,  5,
	-18, -2,-39, 22,  9, 28, -7,-34, 39,-38,-38, 40, 42,-21, 26, 25,-12,  7,-42,-45,  3, 28, 43,-37,
	 -8, 15, 24,-33, 25,-37,-48, 24, 33,  9, -6,-36,  7, -3,-49,-16,-34, 29,-19,  3,-33, 10,-24, 15,
	 10, 12,-11,-11, 44,-14, 18,  1, 10, 25, 10,  9, 19, 25, -5,-42,-27, 41,-35, 33,  4, 50,-42, -6,
	 27, 38, 47,-32,-19,-20, 30,  4, 29,-27, 24, 25,-39, 46,-50, 27, 32, 37,-42,-10,-24, 30, -7, 41,
	-45, 29, 48, 16,  5, 16,  7,-33,-48,-24, 48, 26,-32,-24,-35,-36, 37,  8,  5,-36, 35, 12,-15,  1
};

inline static constexpr std::size_t
mat_o_m = 24, mat_o_n = 12;

/* transpose of mat_m */
inline static constexpr double 
mat_o[mat_o_m*mat_o_n] = {
	 47,  38,  41,  -1,  49,  13,  13,  31,  26,  30,  39,  20,
	-14, -38,  -2,  -9, -44,  44, -25, -37,  32, -14, -47, -13,
	  0, -28,  43,  -1, -12, -33,  42, -37,  12,  47, -26,  14,
	-47, -22, -15, -26, -25,  14,  46,   7,  -6, -21, -44, -37,
	 45, -35,  13, -14, -42,  36, -16,  39, -28, -44, -27, -47,
	 14,  -1, -23, -16,  -8, -28,   7,  -7,   2, -32,  10, -44,
	-26, -29, -33,  16,  -3,  16,   0, -35,  -9, -49, -40,  49,
	-18,  -2, -39,  22,   9,  28,  -7, -34,  39, -38, -38,  40,
	 -8,  15,  24, -33,  25, -37, -48,  24,  33,   9,  -6, -36,
	 10,  12, -11, -11,  44, -14,  18,   1,  10,  25,  10,   9,
	 27,  38,  47, -32, -19, -20,  30,   4,  29, -27,  24,  25,
	-45,  29,  48,  16,   5,  16,   7, -33, -48, -24,  48,  26,
	 10,  42,  26,  38,  32,  26,  -8,  45,  40,  44,  -1,  -1,
	-16,  40, -13, -39,  28, -11, -26, -10, -40, -37,  44,  46,
	  8, -44, -27, -15,  32, -48, -46, -33,  15,  23,  15,  -5,
	  5, -20,  24, -31,  19, -32, -13,  13,  28, -42,  43,  28,
	 -1,  -6,  -5, -19,   1,   1,  32,  29,  14, -12,  31,   3,
	-15,  44,  38,   5,  12,   9, -29, -20,  -3, -27,  34, -31,
	-27, -33, -27,  -6, -19,  42,  -7, -32,  40,  48,  -6, -39,
	-24,  -9,   9, -24,  10,  21, -28, -38, -20, -18,  -8,   1,
	-41, -24,  30, -47,  43,  23,  -1,   8, -26,  -4,  46,   5,
	  2, -27,  -1,  12,  18, -10, -13,  49, -46,  39,  41,  30,
	-40, -24, -16,  18, -36,  22, -39,  15,  -1,  28,  22,  40,
	 39, -17,  20, -30, -47,  24,   0,  -2,  40,  11,  12,  36
};

inline static constexpr std::size_t
mat_p_m = 3, mat_p_n = 20;

inline static constexpr double 
mat_p[mat_p_m*mat_p_n] = {
	47, 38, 41, -1, 49, 13, 13, 31, 26, 30, 39, 20, 31, 41, 37, 41, 13, 40, 22, 0,
	14,-38, -2, -9,-44, 44,-25,-37, 32,-14,-47,-13, 46, -1, 30,-36, -8, 42, 29, 0,
	10,-28, 43, -1,-12,-33, 42,-37, 12, 47,-26, 14, 18, 26, 24,-11, 16,-33, 21, 0
};

inline static constexpr std::size_t
mat_q_m = 1, mat_q_n = 1;

inline static constexpr double
mat_q[mat_q_m*mat_q_n] = {
	-91.52
};

inline static constexpr std::size_t
mat_r_m = 1, mat_r_n = 1;

inline static constexpr double
mat_r[mat_r_m*mat_r_n] = {
	0
};

inline static constexpr std::size_t
mat_s_m = 5, mat_s_n = 1;

inline static constexpr double
mat_s[mat_s_m*mat_s_n] = {
	-156.123,
	64.512,
	0,
	122,
	-9.3156
};

inline static constexpr std::size_t
mat_t_m = 2, mat_t_n = 1;

inline static constexpr double
mat_t[mat_t_m*mat_t_n] = {
	16.3,
	-0.3156
};

inline static constexpr std::size_t
mat_u_m = 2, mat_u_n = 1;

inline static constexpr double
mat_u[mat_u_m*mat_u_n] = {
	0,
	994
};

inline static constexpr std::size_t
mat_v_m = 2, mat_v_n = 1;

inline static constexpr double
mat_v[mat_v_m*mat_v_n] = {
	0,
	0
};

inline static constexpr std::size_t
mat_w_m = 2, mat_w_n = 1;

inline static constexpr double
mat_w[mat_w_m*mat_w_n] = {
	2,
	0
};

inline static constexpr std::size_t
mat_x_m = 5, mat_x_n = 5;

inline static constexpr double
mat_x[mat_x_m*mat_x_n] = {
	2, 0, 0, 0, 0,
	0,-9, 0, 0, 0,
	0, 0,.2, 0, 0,
	0, 0, 0, 9, 0,
	0, 0, 0, 0,.7
};

inline static constexpr std::size_t
mat_y_m = 5, mat_y_n = 5;

inline static constexpr double
mat_y[mat_y_m*mat_y_n] = {
	13, 22.5,   0,   0,   0,
	 0,   -9,   4,   0,   0,
	 0,    0,  .2,   2,   0,
	 0,    0,   0,   9,  -1,
	 0,    0,   0,   0,  .7
};

inline static constexpr std::size_t
mat_z_m = 5, mat_z_n = 5;

inline static constexpr double
mat_z[mat_z_m*mat_z_n] = {
	0, 22.5,   0,   0,   0,
	0,   -9,   4,   0,   0,
	0,    0,  .2,   2,   0,
	0,    0,   0,   0,  -1,
	0,    0,   0,   0,  .7
};

inline static constexpr std::size_t
mat_aa_m = 5, mat_aa_n = 5;

inline static constexpr double
mat_aa[mat_aa_m*mat_aa_n] = {
	1, 92.6,   0,   0,   0,
	0,   -9,   0,   0,   0,
	0,    0,  .4,   0,   0,
	0,    0,   0,   1,  -9,
	0,    0,   0,   0,  .7
};

inline static constexpr std::size_t
mat_ab_m = 6, mat_ab_n = 6;

inline static constexpr double
mat_ab[mat_ab_m*mat_ab_n] = {
	4, 92.6, -.1, 104, 900, 4.2,
	0,   -9, .17,  65,  99,  -7,
	0,    0,  .4,  44,  78,  33,
	0,    0,   0,   1,  -9, 112,
	0,    0,   0,   0,  .9, 789,
	0,    0,   0,   0,   0, .89
};

inline static constexpr std::size_t
mat_ac_m = 6, mat_ac_n = 6;

inline static constexpr double
mat_ac[mat_ac_m*mat_ac_n] = {
	  4,    0,   0,   0,   0,   0,
	 74,   19,   0,   0,   0,   0,
	-74,  -60,  .4,   0,   0,   0,
	421,   40,  44,  11,   0,   0,
	662, -120, 110, .12, 339,   0,
	-.4,   .9, -49,  -2,  77, -49
};

inline static constexpr std::size_t
mat_ad_m = 5, mat_ad_n = 5;

inline static constexpr double
mat_ad[mat_ad_m*mat_ad_n] = {
	-42, 111,  -3,   2,   1,
	111,   0, .21,   4,  89,
	 -3, .21,  14,   0,  70,
	  2,   4,   0,  .1,  -9,
	  1,  89,  70,  -9, 217
};

inline static constexpr std::size_t
mat_ae_m = 5, mat_ae_n = 5;

inline static constexpr double
mat_ae[mat_ae_m*mat_ae_n] = {
	0, 0, 0, 1, 0,
	1, 0, 0, 0, 0,
	0, 1, 0, 0, 0,
	0, 0, 0, 0, 1,
	0, 0, 1, 0, 0
};

inline static constexpr std::size_t
mat_af_m = 6, mat_af_n = 6;

inline static constexpr double
mat_af[mat_af_m*mat_af_n] = {
	0, 11,  0,  0,  0,  0,
	0,  0, 22,  0,  0,  0,
	0,  0,  0, 33,  0,  0,
	0,  0,  0,  0, 44,  0,
	0,  0,  0,  0,  0, 55,
	0,  0,  0,  0,  0,  0
};

inline static constexpr std::size_t
mat_ag_m = 5, mat_ag_n = 5;

inline static constexpr double
mat_ag[mat_ag_m*mat_ag_n] = {
	9, 7, 0, 0, 0,
	0, 8, 1, 0, 0,
	0, 0, 4, 6, 0,
	0, 0, 0, 7, 5,
	0, 0, 0, 0, 0
};

inline static constexpr std::size_t
mat_ah_m = 5, mat_ah_n = 5;

inline static constexpr double
mat_ah[mat_ah_m*mat_ah_n] = {
	9, 0, 0, 0, 0,
	0, 8, 0, 0, 0,
	0, 0, 4, 6, 0,
	0, 0, 0, 7, 5,
	0, 0, 0, 0, 0
};

inline static constexpr std::size_t
mat_ai_m = 6, mat_ai_n = 6;

inline static constexpr double
mat_ai[mat_ai_m*mat_ai_n] = {
	9, 7, 0, 0, 0, 0,
	0, 8, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 6, 0, 0,
	0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 8,
};

inline static constexpr std::size_t
mat_aj_m = 2, mat_aj_n = 2;

inline static constexpr double
mat_aj[mat_aj_m*mat_aj_n] = {
	0, 2,
	2, 0
};

/* namespace detail */ }
HBRS_MPL_NAMESPACE_END

#endif // !HBRS_MPL_DETAIL_TEST_FWD_HPP
