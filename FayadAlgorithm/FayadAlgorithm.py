# Generic Imports
import numpy as np
import math


class FayadAlgorithm:
    def __init__(self, dataset):
        self.dataset = dataset  # Dictionary to store the given input data.

    def process_data(self, data_set=None, boundaries=set([]), max_cp=None):
        '''
        This method performs the actual algorithm. It performs the discretization and results the cut-points along
        with the values of each intervals
        :param data_set:
        :param boundaries:
        :param max_cp:
        :return:
        '''
        ds = self.dataset if data_set is None else data_set
        cut_points = self.calc_cut_points(ds)
        max_gain = float('-inf')
        if len(cut_points) == 0:
            return boundaries
        for cp in cut_points:
            rst = self.calc_gain(ds, cp)
            print(cp, rst)
            if rst['qualified']:
                boundaries.add(cp)
                return boundaries
            if rst['gain'] > max_gain:
                max_gain = rst['gain']
                max_cp = cp

        if max_cp is None:
            return boundaries
        splitted = self.split_dataset(ds, max_cp)
        boundaries.update(self.process_data(splitted[0], boundaries, max_cp))
        boundaries.update(self.process_data(splitted[1], boundaries, max_cp))
        return boundaries

    def calc_cut_points(self, dataset):
        '''
        This method finds the possible cut-points T from the dataset.
        :param dataset:
        :return: cut_points
        '''
        cut_points = []
        array = dataset['data']
        for i in range(len(array) - 1):
            cut_points.append(np.average([array[i][0], array[i + 1][0]]))
        return cut_points

    def split_dataset(self, dataset, cut_point):
        '''
        This method is called to split the dataset based on given cut-point
        :param dataset:
        :param cut_point:
        :return:
        '''
        result = [{'class': set([]), 'data': []}, {'class': set([]), 'data': []}]
        for item in dataset['data']:
            if item[0] <= cut_point:
                result[0]['class'].add(item[1])
                result[0]['data'].append(item)
            else:
                result[1]['class'].add(item[1])
                result[1]['data'].append(item)
        return result

    def calc_gain(self, dataset, cut_point):
        '''
        This method iteratively claculates the Gain(S,T) based on the chosen cut-point.
        :param dataset:
        :param cut_point:
        :return:
        '''
        splitted_result = self.split_dataset(dataset, cut_point)
        sub_ent_values = []
        info_value = 0
        N = len(dataset['data'])
        for sub_set in splitted_result:
            sub_set_ent = self.entropy(sub_set['data'], sub_set['class'])
            sub_ent_values.append((sub_set_ent, len(sub_set['class'])))
            info_value += (len(sub_set['data']) * sub_set_ent) / N

        overall_entropy = self.entropy(dataset['data'], dataset['class'])
        gain = overall_entropy - info_value
        delta = self.calc_delta(sub_ent_values, overall_entropy, len(dataset['class']), N)
        return {'gain': gain, 'delta': delta, 'qualified':  gain - delta > 0.0}

    def calc_delta(self, sub_ent_values, all_entropy, k, N):
        sum = 0
        for ent in sub_ent_values:
            sum += (ent[1] * ent[0])
        f = math.log2(math.pow(3, k) - 2) - (
            (k * all_entropy) - sum
        )
        return (np.log2(N - 1) + f) / N

    def entropy(self, dataset, class_list):
        '''
        This method finds the entropy for every partition T
        :return:
        '''
        temp = {}
        for clz in class_list:
            temp[clz] = 0
            for item in dataset:
                if item[1] == clz:
                    temp[clz] += 1
        entropy_value = 0
        for k in temp.keys():
            p = temp[k] / len(dataset)
            entropy_value += (p * math.log2(p))
        return - entropy_value