import argparse
from FileReader import FileReader
from FayadAlgorithm import FayadAlgorithm

def process_console_args():
    parser = argparse.ArgumentParser('TwitterExtractor.py')
    parser.add_argument('-c', '--cutpoint', metavar='<cut-point>', default='0.5',
                        help='The cut-point in percentage in the range from the lowest value to the highest '
                             'value of the input data.')
    parser.add_argument('file', metavar='<input file',
                        help='The path to the input file')
    args = parser.parse_args()
    return args


def readfile(file_path):
    file_reader = FileReader(file_path)
    dict = file_reader.readfile()
    print(dict)


def main(args):
    filepath = args.file
    cutpoint = args.cutpoint

    dictionary = readfile(filepath);
    FayadAlgorithm()

if __name__ == '__main__':
    main(process_console_args())
