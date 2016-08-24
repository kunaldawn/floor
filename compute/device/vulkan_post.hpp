/*
 *  Flo's Open libRary (floor)
 *  Copyright (C) 2004 - 2016 Florian Ziesche
 *  
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; version 2 of the License only.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef __FLOOR_COMPUTE_DEVICE_VULKAN_POST_HPP__
#define __FLOOR_COMPUTE_DEVICE_VULKAN_POST_HPP__

#if defined(FLOOR_COMPUTE_VULKAN)

// NOTE: very wip

//////////////////////////////////////////
// vertex shader
// returns the vertex id inside a vertex shader
const_func uint32_t get_vertex_id() asm("floor.builtin.vertex_id.i32");
// returns the instance id inside a vertex shader
const_func uint32_t get_instance_id() asm("floor.builtin.instance_id.i32");

#define vertex_id get_vertex_id()
#define instance_id get_instance_id()

//////////////////////////////////////////
// fragment shader
//! returns the normalized (in [0, 1]) point coordinate (clang_float2 version)
const_func clang_float2 get_point_coord_cf2() asm("floor.builtin.point_coord.float2");
//! returns the normalized (in [0, 1]) point coordinate
floor_inline_always const_func float2 get_point_coord() { return float2::from_clang_vector(get_point_coord_cf2()); }
//! discards the current fragment
void discard_fragment() __attribute__((noreturn)) asm("floor.discard_fragment");
//! partial derivative of p with respect to the screen-space x coordinate
const_func float dfdx(float p) asm("floor.dfdx.f32");
//! partial derivative of p with respect to the screen-space y coordinate
const_func float dfdy(float p) asm("floor.dfdy.f32");
//! returns "abs(dfdx(p)) + abs(dfdy(p))"
const_func float fwidth(float p) asm("floor.fwidth.f32");
//! computes the partial deriviate of p with respect to the screen-space (x, y) coordinate
floor_inline_always const_func pair<float, float> dfdx_dfdy_gradient(const float& p) {
	return { { dfdx(p) }, { dfdy(p) } };
}
//! computes the partial deriviate of p with respect to the screen-space (x, y) coordinate
floor_inline_always const_func pair<float2, float2> dfdx_dfdy_gradient(const float2& p) {
	return { { dfdx(p.x), dfdx(p.y) }, { dfdy(p.x), dfdy(p.y) } };
}
//! computes the partial deriviate of p with respect to the screen-space (x, y) coordinate
floor_inline_always const_func pair<float3, float3> dfdx_dfdy_gradient(const float3& p) {
	return { { dfdx(p.x), dfdx(p.y), dfdx(p.z) }, { dfdy(p.x), dfdy(p.y), dfdx(p.z) } };
}

#endif

#endif