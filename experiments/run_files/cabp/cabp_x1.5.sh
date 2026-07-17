#!/bin/bash

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT_DIR="$(cd "$SCRIPT_DIR/../../.." && pwd)"

build_dir="$ROOT_DIR/build"
dataset_dir="$ROOT_DIR/benchmarks/cabp"
report_dir="$ROOT_DIR/experiments/results/cabp/cabp_x1.5"
time_limit="1800"
vertices_mode="has_hole"
target_value_mode="cabp"

mkdir -p "$report_dir"

$build_dir/cplex $dataset_dir/A-pores_1.mtx.rnd    9   10  45      $time_limit  $vertices_mode $target_value_mode > $report_dir/A-pores_1.txt
$build_dir/cplex $dataset_dir/B-ibm32.mtx.rnd      12  13  48      $time_limit  $vertices_mode $target_value_mode > $report_dir/B-ibm32.txt
$build_dir/cplex $dataset_dir/C-bcspwr01.mtx.rnd   19  20  59      $time_limit  $vertices_mode $target_value_mode > $report_dir/C-bcspwr01.txt
$build_dir/cplex $dataset_dir/D-bcsstk01.mtx.rnd   12  13  72      $time_limit  $vertices_mode $target_value_mode > $report_dir/D-bcsstk01.txt
$build_dir/cplex $dataset_dir/E-bcspwr02.mtx.rnd   24  25  74      $time_limit  $vertices_mode $target_value_mode > $report_dir/E-bcspwr02.txt
$build_dir/cplex $dataset_dir/F-curtis54.mtx.rnd   15  16  81      $time_limit  $vertices_mode $target_value_mode > $report_dir/F-curtis54.txt
$build_dir/cplex $dataset_dir/G-will57.mtx.rnd     16  17  86      $time_limit  $vertices_mode $target_value_mode > $report_dir/G-will57.txt
$build_dir/cplex $dataset_dir/H-impcol_b.mtx.rnd   10  11  89      $time_limit  $vertices_mode $target_value_mode > $report_dir/H-impcol_b.txt
$build_dir/cplex $dataset_dir/I-ash85.mtx.rnd      31  32  128     $time_limit  $vertices_mode $target_value_mode > $report_dir/I-ash85.txt
$build_dir/cplex $dataset_dir/J-nos4.mtx.rnd       48  49  150     $time_limit  $vertices_mode $target_value_mode > $report_dir/J-nos4.txt
$build_dir/cplex $dataset_dir/K-dwt__234.mtx.rnd   69  70  176     $time_limit  $vertices_mode $target_value_mode > $report_dir/K-dwt__234.txt
$build_dir/cplex $dataset_dir/L-bcspwr03.mtx.rnd   43  44  178     $time_limit  $vertices_mode $target_value_mode > $report_dir/L-bcspwr03.txt
$build_dir/cplex $dataset_dir/M-bcsstk06.mtx.rnd   49  50  630     $time_limit  $vertices_mode $target_value_mode > $report_dir/M-bcsstk06.txt
$build_dir/cplex $dataset_dir/N-bcsstk07.mtx.rnd   49  50  630     $time_limit  $vertices_mode $target_value_mode > $report_dir/N-bcsstk07.txt
$build_dir/cplex $dataset_dir/O-impcol_d.mtx.rnd   157 158 638     $time_limit  $vertices_mode $target_value_mode > $report_dir/O-impcol_d.txt
$build_dir/cplex $dataset_dir/P-can__445.mtx.rnd   130 131 668     $time_limit  $vertices_mode $target_value_mode > $report_dir/P-can__445.txt
$build_dir/cplex $dataset_dir/Q-494_bus.mtx.rnd    246 247 741     $time_limit  $vertices_mode $target_value_mode > $report_dir/Q-494_bus.txt
$build_dir/cplex $dataset_dir/R-dwt__503.mtx.rnd   93  94  755     $time_limit  $vertices_mode $target_value_mode > $report_dir/R-dwt__503.txt
$build_dir/cplex $dataset_dir/S-sherman4.mtx.rnd   387 388 819     $time_limit  $vertices_mode $target_value_mode > $report_dir/S-sherman4.txt
$build_dir/cplex $dataset_dir/T-dwt__592.mtx.rnd   169 170 888     $time_limit  $vertices_mode $target_value_mode > $report_dir/T-dwt__592.txt
$build_dir/cplex $dataset_dir/U-662_bus.mtx.rnd    247 248 993     $time_limit  $vertices_mode $target_value_mode > $report_dir/U-662_bus.txt
$build_dir/cplex $dataset_dir/V-nos6.mtx.rnd       492 493 1013    $time_limit  $vertices_mode $target_value_mode > $report_dir/V-nos6.txt
$build_dir/cplex $dataset_dir/W-685_bus.mtx.rnd    171 172 1028    $time_limit  $vertices_mode $target_value_mode > $report_dir/W-685_bus.txt
$build_dir/cplex $dataset_dir/X-can__715.mtx.rnd   151 152 1073    $time_limit  $vertices_mode $target_value_mode > $report_dir/X-can__715.txt