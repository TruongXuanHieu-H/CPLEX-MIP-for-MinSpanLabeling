#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks/abp"
report_dir="$ROOT_DIR/experiments/results/abp/abp_x1.25"
time_limit="1800"

mkdir -p "$report_dir"

$build_dir/cplex $dataset_dir/A-pores_1.mtx.rnd    7   8   38  $time_limit  has_hole    > $report_dir/A-pores_1.txt
$build_dir/cplex $dataset_dir/B-ibm32.mtx.rnd      11  12  40  $time_limit  has_hole    > $report_dir/B-ibm32.txt
$build_dir/cplex $dataset_dir/C-bcspwr01.mtx.rnd   21  22  49  $time_limit  has_hole    > $report_dir/C-bcspwr01.txt
$build_dir/cplex $dataset_dir/D-bcsstk01.mtx.rnd   11  12  60  $time_limit  has_hole    > $report_dir/D-bcsstk01.txt
$build_dir/cplex $dataset_dir/E-bcspwr02.mtx.rnd   26  27  62  $time_limit  has_hole    > $report_dir/E-bcspwr02.txt
$build_dir/cplex $dataset_dir/F-curtis54.mtx.rnd   16  17  68  $time_limit  has_hole    > $report_dir/F-curtis54.txt
$build_dir/cplex $dataset_dir/G-will57.mtx.rnd     16  17  72  $time_limit  has_hole    > $report_dir/G-will57.txt
$build_dir/cplex $dataset_dir/H-impcol_b.mtx.rnd   10  11  74  $time_limit  has_hole    > $report_dir/H-impcol_b.txt
$build_dir/cplex $dataset_dir/I-ash85.mtx.rnd      28  29  107 $time_limit  has_hole    > $report_dir/I-ash85.txt
$build_dir/cplex $dataset_dir/J-nos4.mtx.rnd       43  44  125 $time_limit  has_hole    > $report_dir/J-nos4.txt
$build_dir/cplex $dataset_dir/K-dwt__234.mtx.rnd   63  64  147 $time_limit  has_hole    > $report_dir/K-dwt__234.txt
$build_dir/cplex $dataset_dir/L-bcspwr03.mtx.rnd   48  49  148 $time_limit  has_hole    > $report_dir/L-bcspwr03.txt
$build_dir/cplex $dataset_dir/M-bcsstk06.mtx.rnd   42  43  525 $time_limit  has_hole    > $report_dir/M-bcsstk06.txt
$build_dir/cplex $dataset_dir/N-bcsstk07.mtx.rnd   42  43  525 $time_limit  has_hole    > $report_dir/N-bcsstk07.txt
$build_dir/cplex $dataset_dir/O-impcol_d.mtx.rnd   150 151 532 $time_limit  has_hole    > $report_dir/O-impcol_d.txt
$build_dir/cplex $dataset_dir/P-can__445.mtx.rnd   112 113 557 $time_limit  has_hole    > $report_dir/P-can__445.txt
$build_dir/cplex $dataset_dir/Q-494_bus.mtx.rnd    283 284 618 $time_limit  has_hole    > $report_dir/Q-494_bus.txt
$build_dir/cplex $dataset_dir/R-dwt__503.mtx.rnd   78  79  629 $time_limit  has_hole    > $report_dir/R-dwt__503.txt
$build_dir/cplex $dataset_dir/S-sherman4.mtx.rnd   326 327 683 $time_limit  has_hole    > $report_dir/S-sherman4.txt
$build_dir/cplex $dataset_dir/T-dwt__592.mtx.rnd   141 142 740 $time_limit  has_hole    > $report_dir/T-dwt__592.txt
$build_dir/cplex $dataset_dir/U-662_bus.mtx.rnd    275 276 828 $time_limit  has_hole    > $report_dir/U-662_bus.txt
$build_dir/cplex $dataset_dir/V-nos6.mtx.rnd       411 412 844 $time_limit  has_hole    > $report_dir/V-nos6.txt
$build_dir/cplex $dataset_dir/W-685_bus.mtx.rnd    170 171 857 $time_limit  has_hole    > $report_dir/W-685_bus.txt
$build_dir/cplex $dataset_dir/X-can__715.mtx.rnd   145 146 894 $time_limit  has_hole    > $report_dir/X-can__715.txt