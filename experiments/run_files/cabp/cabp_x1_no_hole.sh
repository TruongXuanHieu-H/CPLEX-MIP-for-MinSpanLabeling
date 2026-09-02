#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks/cabp"
report_dir="$ROOT_DIR/experiments/results/cabp/cabp_x1"
time_limit="1800"
vertices_mode="has_hole"
target_value_mode="cabp"

mkdir -p "$report_dir"

$build_dir/cplex $dataset_dir/A-pores_1.mtx.rnd    6   7   30      $time_limit  $vertices_mode $target_value_mode > $report_dir/A-pores_1.txt
$build_dir/cplex $dataset_dir/B-ibm32.mtx.rnd      8   9   32      $time_limit  $vertices_mode $target_value_mode > $report_dir/B-ibm32.txt
$build_dir/cplex $dataset_dir/C-bcspwr01.mtx.rnd   13  14  39      $time_limit  $vertices_mode $target_value_mode > $report_dir/C-bcspwr01.txt
$build_dir/cplex $dataset_dir/D-bcsstk01.mtx.rnd   8   9   48      $time_limit  $vertices_mode $target_value_mode > $report_dir/D-bcsstk01.txt
$build_dir/cplex $dataset_dir/E-bcspwr02.mtx.rnd   16  17  49      $time_limit  $vertices_mode $target_value_mode > $report_dir/E-bcspwr02.txt
$build_dir/cplex $dataset_dir/F-curtis54.mtx.rnd   10  11  54      $time_limit  $vertices_mode $target_value_mode > $report_dir/F-curtis54.txt
$build_dir/cplex $dataset_dir/G-will57.mtx.rnd     11  12  57      $time_limit  $vertices_mode $target_value_mode > $report_dir/G-will57.txt
$build_dir/cplex $dataset_dir/H-impcol_b.mtx.rnd   7   8   59      $time_limit  $vertices_mode $target_value_mode > $report_dir/H-impcol_b.txt
$build_dir/cplex $dataset_dir/I-ash85.mtx.rnd      21  22  85      $time_limit  $vertices_mode $target_value_mode > $report_dir/I-ash85.txt
$build_dir/cplex $dataset_dir/J-nos4.mtx.rnd       32  33  100     $time_limit  $vertices_mode $target_value_mode > $report_dir/J-nos4.txt
$build_dir/cplex $dataset_dir/K-dwt__234.mtx.rnd   46  47  117     $time_limit  $vertices_mode $target_value_mode > $report_dir/K-dwt__234.txt
$build_dir/cplex $dataset_dir/L-bcspwr03.mtx.rnd   29  30  118     $time_limit  $vertices_mode $target_value_mode > $report_dir/L-bcspwr03.txt
$build_dir/cplex $dataset_dir/M-bcsstk06.mtx.rnd   33  34  420     $time_limit  $vertices_mode $target_value_mode > $report_dir/M-bcsstk06.txt
$build_dir/cplex $dataset_dir/N-bcsstk07.mtx.rnd   33  34  420     $time_limit  $vertices_mode $target_value_mode > $report_dir/N-bcsstk07.txt
$build_dir/cplex $dataset_dir/O-impcol_d.mtx.rnd   105 106 425     $time_limit  $vertices_mode $target_value_mode > $report_dir/O-impcol_d.txt
$build_dir/cplex $dataset_dir/P-can__445.mtx.rnd   87  88  445     $time_limit  $vertices_mode $target_value_mode > $report_dir/P-can__445.txt
$build_dir/cplex $dataset_dir/Q-494_bus.mtx.rnd    164 165 494     $time_limit  $vertices_mode $target_value_mode > $report_dir/Q-494_bus.txt
$build_dir/cplex $dataset_dir/R-dwt__503.mtx.rnd   62  63  503     $time_limit  $vertices_mode $target_value_mode > $report_dir/R-dwt__503.txt
$build_dir/cplex $dataset_dir/S-sherman4.mtx.rnd   258 259 546     $time_limit  $vertices_mode $target_value_mode > $report_dir/S-sherman4.txt
$build_dir/cplex $dataset_dir/T-dwt__592.mtx.rnd   113 114 592     $time_limit  $vertices_mode $target_value_mode > $report_dir/T-dwt__592.txt
$build_dir/cplex $dataset_dir/U-662_bus.mtx.rnd    165 166 662     $time_limit  $vertices_mode $target_value_mode > $report_dir/U-662_bus.txt
$build_dir/cplex $dataset_dir/V-nos6.mtx.rnd       328 329 675     $time_limit  $vertices_mode $target_value_mode > $report_dir/V-nos6.txt
$build_dir/cplex $dataset_dir/W-685_bus.mtx.rnd    114 115 685     $time_limit  $vertices_mode $target_value_mode > $report_dir/W-685_bus.txt
$build_dir/cplex $dataset_dir/X-can__715.mtx.rnd   101 102 715     $time_limit  $vertices_mode $target_value_mode > $report_dir/X-can__715.txt