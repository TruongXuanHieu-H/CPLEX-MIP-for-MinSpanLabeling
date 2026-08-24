import os
import re
import argparse
import pandas as pd


def extract(pattern, text, default="-"):
    m = re.search(pattern, text, re.MULTILINE)
    return m.group(1).strip() if m else default


def parse_log(filepath):
    with open(filepath, "r", encoding="utf-8", errors="ignore") as f:
        content = f.read()

    problem_path = extract(
        r'! Solving for graph\s+([^\n\r]+)',
        content
    )

    problem = os.path.basename(problem_path)

    time_limit = extract(
        r'!\s*Time limit is set to\s*(\d+)',
        content
    )

    worker_count = extract(
        r'Parallel mode: .*?, using up to (\d+) threads\.',
        content
    )

    target_value = extract(
        r'!\s*Target value is set to\s*(\d+)',
        content
    )

    lower_bound = extract(
        r'!\s*Lower bound is set to\s*(\d+)',
        content
    )

    upper_bound = extract(
        r'!\s*Upper bound is set to\s*(\d+)',
        content
    )

    time_consumed = extract(
        r'Total \(root\+branch&cut\)\s*=\s*([\d.]+)\s*sec\.',
        content
    )

    status = extract(
        r'!\s*Status:\s*(.*)',
        content
    )

    if status.startswith("OPTIMAL"):
        result = "OPTIMAL"
    elif status.startswith("FEASIBLE"):
        result = "FEASIBLE"
    else:
        result = "UNKNOWN"

    optimal_found = "x" if result == "OPTIMAL" else ""

    max_label = extract(
        r'!\s*Best span\s*=\s*(\d+)',
        content
    ) if result in ["OPTIMAL", "FEASIBLE"] else "-"

    best_span = int(max_label) - 1 if max_label != "-" else "-"


    return {
        "File": os.path.basename(filepath),
        "Problem": problem,
        "Time limit (s)": time_limit,
        "Worker count": worker_count,
        "Target value": target_value,
        "Lower bound": lower_bound,
        "Upper bound": upper_bound,
        "Best span": best_span,
        "Time consumed (s)": time_consumed,
        "Optimal found": optimal_found
    }


def main(root_dir, output_file):
    with pd.ExcelWriter(
        output_file,
        engine="openpyxl"
    ) as writer:

        for folder in sorted(os.listdir(root_dir)):
            folder_path = os.path.join(root_dir, folder)

            if not os.path.isdir(folder_path):
                continue

            rows = []

            for filename in sorted(os.listdir(folder_path)):
                if not filename.endswith(".txt"):
                    continue

                filepath = os.path.join(folder_path, filename)

                try:
                    rows.append(parse_log(filepath))
                except Exception as e:
                    print(f"Error parsing {filepath}: {e}")

            if not rows:
                continue

            df = pd.DataFrame(rows)

            columns = [
                "File",
                "Problem",
                "Time limit (s)",
                "Worker count",
                "Target value",
                "Lower bound",
                "Upper bound",
                "Best span",
                "Time consumed (s)",
                "Optimal found"
            ]

            df = df[columns]

            sheet_name = folder[:31]

            df.to_excel(
                writer,
                sheet_name=sheet_name,
                index=False
            )

    print(f"Saved to {output_file}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Parse CPLEX-MIP logs into an Excel summary."
    )

    parser.add_argument(
        "root_dir",
        help="Root directory containing experiment folders"
    )

    parser.add_argument(
        "output_file",
        help="Output Excel file"
    )

    args = parser.parse_args()

    main(args.root_dir, args.output_file)