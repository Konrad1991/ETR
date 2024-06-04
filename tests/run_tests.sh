#!/bin/bash

compile() {
	local path="$1"
	g++ $path -std=c++20 >/dev/null 2>&1 &
	local pid=$!
	wait $pid
	local exit_status=$?
	if [ $exit_status -ne 0 ]; then
		echo "$path compilation failed  $exit_status"
	else
		echo "$path compiled successfully"
	fi
}

run_silently_and_check() {
	local path="$1"
	local print_output="$2"
	compile $path
	local command="./a.out"

	if [ "$print_output" = "true" ]; then
		"$command"
	else
		$command >/dev/null 2>&1 &
	fi
	local pid=$!
	wait $pid
	local exit_status=$?

	if [ $exit_status -ne 0 ]; then
		echo "$path encountered a runtime error with exit status $exit_status"
	else
		echo "$path ran successfully"
	fi

	return $exit_status
}

cd /home/konrad/Documents/GitHub/RProjects/etr_supplement/ETR/tests

run_silently_and_check BaseStore_Tests.cpp false
run_silently_and_check BinaryOperations_Tests.cpp false
run_silently_and_check Borrow_Tests.cpp false
run_silently_and_check CMR_Tests.cpp false
run_silently_and_check Coca_Tests.cpp false
run_silently_and_check Colon_Tests.cpp false
run_silently_and_check Concepts_Tests.cpp false
run_silently_and_check Derivatives_Tests.cpp false
run_silently_and_check Helper_Tests.cpp false
run_silently_and_check Rep_Tests.cpp false
run_silently_and_check Subsetting_Tests.cpp false
run_silently_and_check Unary_Tests.cpp false
run_silently_and_check Vector_Tests.cpp false
