// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/option.hpp>

int main(int argc, char** argv)
{
    if (argc != 2) return 1;

    std::hash<ocl::crc_hash_trait> hash{};

    ocl::io::enable_stdio_sync(false);
	ocl::io::print(hash.operator()<true, false>(argv[1]));

	return 0;
}
