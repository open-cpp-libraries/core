// Copyright 2025, Amlal El Mahrouss (amlal@nekernel.org)
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
// Official repository: https://github.com/ocl-org/core

#include <ocl/crc_hash.hpp>
#include <ocl/print.hpp>
#include <ocl/smart_ptr.hpp>

/// \brief Smart pointer example.
auto main(int argc, char** argv) -> int
{
    ocl::shared_ptr<std::ostream> smart = ocl::delete_ptr(&std::cout);
    *smart << "hello, world\n";

    ocl::tracked_ptr<int> tracked = ocl::make_tracked<int>(10);
    *smart << *tracked << "\n";
    
	return EXIT_SUCCESS;
}
