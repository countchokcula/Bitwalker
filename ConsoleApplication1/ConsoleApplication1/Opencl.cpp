#include <iostream>
#include <string>
#include <array>
#include <CL/cl.hpp>
#include "OpenCLhelper.h"
#include "stdafx.h"

class blah {/*
	cl::Program program = CreateProgram("processarray.cl");
	auto context = program.getInfo<CL_PROGRAM_CONTEXT>();
	auto devices = context.getInfo<CL_CONTEXT_DEVICES>();
	auto& device = devices.front();

	const int rows = 8;
	std::array<std::string, rows> retarr;
	cl::Buffer Buf(context, CL_MEM_READ_WRITE | CL_MEM_HOST_READ_ONLY | CL_MEM_COPY_HOST_PTR, 100, nullptr);
	cl::Kernel kernel(program, "ProcessMajority");

	kernel.setArg(10, 20);

	cl::CommandQueue que(context, device);
	que.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(4, 8));
	que.enqueueReadBuffer(Buf, GL_TRUE, 0, sizeof(char) * rows * 4, retarr.data());

	std::cout << &kernel;
	std::cin.get();*/
 
};