# Generic Imports
import numpy as np
import math

class FayadAlgorithm:
    def __init__(self, dataset):
        self.dataset = dataset   # Dictionary to store the given input data.

    def calc_cut_points(self, dataset):
        cut_points = []
        for i in range(len(dataset) - 1):
            cut_points.append(np.average([dataset[i][0], dataset[i+1][0]]))
        return cut_points

    def split_dataset(self, dataset, cut_point):
        dataset_list = [[], []]
        for item in dataset:
            if item[0] <= cut_point:
                dataset_list[0].append(item)
            else:
                dataset_list[1].append(item)
        return dataset_list


    def calc_gain(self, dataset, cut_point):
        dataset_list = self.split_dataset(dataset, cut_point)
        info_value = 0
        for sub_set in dataset_list:
            info_value += (len(sub_set) * self.entropy(sub_set, self.dataset['class']) / len(self.dataset))
        overall_entropy = self.entropy(self.dataset, self.dataset['class'])
        return overall_entropy - info_value

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
            p = temp[k]/len(dataset)
            entropy_value += p * math.log2(p)
        return - entropy_value

    def calc_delta(self, ):

        pass


    def preprocessing(self):
        '''
        This method parses a text file and prepare it for the algorithm
        '''
        pass

    def discretization(self):
        '''
        This method should calculate the information gain Gain(S,T) = Ent(S) - I(S,T).
        Algorithm:
        (1) Find T (among possible data points) that minimizes I(S, T) (i.e., max information gain)
        (2) Recursively find new T to the partitions obtained until the terminating criterion is
        met, i.e. Gain(S, T) > delta
        :return:
        '''
        pass



    def terminating_criteria(self):
        '''
        This method computes the terminating criteria (Gain(S,T)> delta) where delta is:
        delta = (log(N-1)/N) + (f(S,T)/N)
        f(S,T) = log(3^k-2)-(k*Ent(S)- k1*Ent(S1) - k2*Ent(S2))
        :return:
        '''
        pass

    def interval_points(self):
        '''
        This method return a list of boundary points and intervals.
        :return:
        '''

