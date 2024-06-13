import json
import numpy as np
import pandas as pd
import argparse
import os


def run(file_input):
    data = None
    with open(file_input) as f:
        data = json.load(f)
    data_new = {}
    for te in data['traceEvents']:
        if(data_new.get(te.get('name')) is None):
            data_new[te.get('name')] = []
        data_new[te.get('name')].append(te.get('dur'))
    sorted_data = sorted(data_new.items(), key=lambda x:x[0])
    report_data = {}
    loop_counts = {}
    for sditm in sorted_data:
        if(report_data.get('function_name') is None):
            report_data['function_name'] = []
        report_data['function_name'].append(sditm[0] + "({})".format(len(sditm[1])))
        if(report_data.get('avg(us)') is None):
            report_data['avg(us)'] = []
        report_data['avg(us)'].append(np.mean(sditm[1]))

        if(report_data.get('min(us)') is None):
            report_data['min(us)'] = []
        report_data['min(us)'].append(np.min(sditm[1]))

        if(report_data.get('max(us)') is None):
            report_data['max(us)'] = []
        report_data['max(us)'].append(np.max(sditm[1]))

        if(report_data.get('std(us)') is None):
            report_data['std(us)'] = []
        report_data['std(us)'].append(np.std(sditm[1]))

    fr_report = pd.DataFrame(report_data)
    fr_report.to_excel('report.xlsx')
    print("Save report.xlsx to path:{}".format(os.getcwd()))


def parse_args():
    parser = argparse.ArgumentParser()
    parser.add_argument("file_in", type=str, help="test json file")
    params = parser.parse_args()
    return params


def main(args): 
    run(args.file_in)


if __name__ == "__main__":
    args = parse_args()
    main(args)
