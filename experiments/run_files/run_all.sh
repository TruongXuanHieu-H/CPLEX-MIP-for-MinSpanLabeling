#!/bin/bash

export TZ='Asia/Ho_Chi_Minh'

scripts=(
    "abp/abp_x1.sh"
    "abp/abp_x1.25.sh"
    "abp/abp_x1.5.sh"
    "abp/abp_x0.5.sh"
    "abp/abp_x0.75.sh"

    "cabp/cabp_x1.sh"
    "cabp/cabp_x1.25.sh"
    "cabp/cabp_x1.5.sh"
    "cabp/cabp_x0.5.sh"
    "cabp/cabp_x0.75.sh"
)

chmod +x "${scripts[@]}"

for script in "${scripts[@]}"; do
    if [ ! -f "$script" ]; then
        echo "Warning: $script not found"
        continue
    fi

    echo "======================================"
    echo "Running $script"
    echo "Started at $(date '+%Y-%m-%d %H:%M:%S %Z')"

    ./"$script"

    echo "Finished at $(date '+%Y-%m-%d %H:%M:%S %Z')"
    echo "======================================"
done