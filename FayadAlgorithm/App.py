# Generic Imports
import argparse
import math
from FileReader import FileReader
from FayadAlgorithm import FayadAlgorithm


def process_console_args():
    '''
    This method to regulate the log console inputs
    :return:
    '''
    parser = argparse.ArgumentParser('App.py')
    parser.add_argument('file', metavar=' input file',
                        help='The path to the input file')
    args = parser.parse_args()
    return args


def readfile(file_path):
    file_reader = FileReader(file_path)
    dict = file_reader.readfile()
    return dict


def main(args):
    filepath = args.file
    dictionary = readfile(filepath)
    #print("Parsed Dataset:")
    #print(dictionary)
    #print("")
    algo = FayadAlgorithm(dictionary)
    boundaries = algo.process_data()
    cut_points = list(boundaries)
    cut_points.sort()
    dictionary['data'].sort(key=lambda tup: tup[0])
    min = math.floor(dictionary['data'][0][0])

    print('INTERVALS:')
    print('======= ', min, ' =======')

    for item in dictionary['data']:
        if len(cut_points) > 0 and item[0] > cut_points[0]:
            print('  ---- ', cut_points.pop(0), ' ----')
        print('    ', item)
    max = math.ceil(dictionary['data'][len(dictionary['data']) - 1][0])
    print('======= ', max, ' =======')


if __name__ == '__main__':
    main(process_console_args())
