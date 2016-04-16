import argparse
from FileReader import FileReader
from FayadAlgorithm import FayadAlgorithm

def process_console_args():
    parser = argparse.ArgumentParser('TwitterExtractor.py')
    parser.add_argument('file', metavar='<input file',
                        help='The path to the input file')
    args = parser.parse_args()
    return args


def readfile(file_path):
    file_reader = FileReader(file_path)
    dict = file_reader.readfile()
    return dict;


def main(args):
    filepath = args.file
    dictionary = readfile(filepath);
    algo = FayadAlgorithm(dictionary)
    algo.calc_cut_point(dictionary['data'])

if __name__ == '__main__':
    main(process_console_args())
