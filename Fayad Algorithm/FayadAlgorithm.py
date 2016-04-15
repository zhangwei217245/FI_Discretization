# Generic Imports


class FayadAlgorithm(object):
    def __init__(self):
        self.dataset = {}   # Dictionary to store the given input data.

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

    def entropy(self):
        '''
        This method finds the entropy for every partition T
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


if __name__ == '__main__':
    FayadAlgorithm()
