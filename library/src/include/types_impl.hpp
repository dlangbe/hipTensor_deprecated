/*******************************************************************************
 *
 * MIT License
 *
 * Copyright 2023 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 *
 *******************************************************************************/

#ifndef HIPTENSOR_LIBRARY_TYPES_IMPL_HPP
#define HIPTENSOR_LIBRARY_TYPES_IMPL_HPP

#include "types.hpp"

namespace hiptensor
{
    // Specialize overrides for runtime HipDataType
    template <>
    struct HipDataType<hip_bfloat16>
    {
        static constexpr auto value = HIP_R_16BF;
    };

    template <>
    struct HipDataType<_Float16>
    {
        static constexpr auto value = HIP_R_16F;
    };

    template <>

    struct HipDataType<float>
    {
        static constexpr auto value = HIP_R_32F;
    };

    template <>
    struct HipDataType<double>
    {
        static constexpr auto value = HIP_R_64F;
    };

    template <>
    struct HipDataType<int8_t>
    {
        static constexpr auto value = HIP_R_8I;
    };

    template <>
    struct HipDataType<uint8_t>
    {
        static constexpr auto value = HIP_R_8U;
    };

    template <>
    struct HipDataType<int16_t>
    {
        static constexpr auto value = HIP_R_16I;
    };

    template <>
    struct HipDataType<uint16_t>
    {
        static constexpr auto value = HIP_R_16U;
    };

    template <>
    struct HipDataType<int32_t>
    {
        static constexpr auto value = HIP_R_32I;
    };

    template <>
    struct HipDataType<uint32_t>
    {
        static constexpr auto value = HIP_R_32U;
    };

    template <>
    struct HipDataType<int64_t>
    {
        static constexpr auto value = HIP_R_64I;
    };

    template <>
    struct HipDataType<uint64_t>
    {
        static constexpr auto value = HIP_R_64U;
    };

} // namespace hiptensor

#endif // HIPTENSOR_LIBRARY_TYPES_IMPL_HPP
