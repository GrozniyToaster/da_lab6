#! /usr/bin/env bash
set -o nounset
set -o pipefail


function log_info()
{
  log_ "info" "$@"
}

function log_error()
{
  log_ "error" "$@"
}

function log_()
{
  local type=$1
  local message=$2
  local date_str=; date_str=$(date +'%Y-%m-%d %H:%M:%S')
  echo "[${type}] [${date_str}] ${message}"
}
function main()
{
  local bin=solution
  log_info "Compiling..."
  if ! make ; then
    log_error "ERROR: Failed to compile file."
    exit 1
  fi

  # log_info "Making unittest..."
  # if ! make test ; then
  #   log_error "ERROR: Failed to run unittest."
  #   return 1
  # fi

  local test_dir="test/tests"
  rm -rf ${test_dir}
  mkdir -p ${test_dir}
  local examples_cnt=10000
  log_info "Generating tests (examples for each test=[${examples_cnt}])..."
  if ! python test/test_generator.py ${test_dir} ${examples_cnt} ; then
    log_error "ERROR: Failed to python generate tests."
    return 1
  fi

  for test_file in $(ls ${test_dir}/*.t); do
    log_info "Executing ${test_file}..."
    if ! ./${bin} < ${test_file} > last_answer ; then
        log_error "ERROR"
        continue
    fi
    local answer_file="${test_file%.*}"
    echo $answer_file

    if ! diff -u "${answer_file}.a" last_answer ; then
        echo "Failed"
    else
        echo "OK"
    fi
  done
}

main $@