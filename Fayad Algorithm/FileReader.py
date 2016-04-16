class FileReader:
    def __init__(self, file_path):
        self.file_path = file_path

    def readfile(self):
        dict = {}
        file_obj = open(self.file_path, 'rt')
        line_num = 0
        data_sign_passed = False
        for line in file_obj:
            if len(line) > 0:
                if line.startswith('End:'):
                    break
                if line.startswith('Class:') and line_num == 0:
                    for key in line.replace("Class:", '').strip().split(','):
                        dict[key] = []
                elif line_num == 1 and line.startswith('Data:'):
                    data_sign_passed = True
                elif line_num > 1 and data_sign_passed:
                    pair = line.strip().split(',')
                    dict.get(pair[1]).append(float(pair[0]))
                else:
                    raise Exception('invalid file format')
            line_num += 1
        return dict
