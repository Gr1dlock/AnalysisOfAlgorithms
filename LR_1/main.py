import distance
import time

if __name__ == '__main__':
    while True:
        print()
        print("Menu")
        print('1 - Levenshtein recursive')
        print('2 - Levenshtein matrix')
        print('3 - Damerau Levenshtein recursive')
        print('4 - Damerau Levenshtein matrix')
        print('5 - Compare times')
        print('0 - Exit')
        choice = int(input('Input menu option: '))

        if choice == 1:
            s1 = input('Input first string: ')
            s2 = input('Input second string: ')
            print('Levenshtein distance:',
                  distance.levenshtein_recursive(s1, s2))

        elif choice == 2:
            s1 = input('Input first string: ')
            s2 = input('Input second string: ')
            print('Levenshtein distance:',
                  distance.levenshtein_matrix(s1, s2, True))

        elif choice == 3:
            s1 = input('Input first string: ')
            s2 = input('Input second string: ')
            print('Levenshtein distance:',
                  distance.damerau_levenshtein_recursive(s1, s2))

        elif choice == 4:
            s1 = input('Input first string: ')
            s2 = input('Input second string: ')
            print('Levenshtein distance:',
                  distance.damerau_levenshtein_matrix(s1, s2, True))

        elif choice == 5:
            s1 = input('Input first string: ')
            s2 = input('Input second string: ')
            time_l_rec = 0
            time_l_matr = 0
            time_dl_rec = 0
            time_dl_matr = 0
            for i in range(100):
                time_1 = time.perf_counter()
                distance.levenshtein_recursive(s1, s2)
                time_2 = time.perf_counter()
                distance.levenshtein_matrix(s1, s2, False)
                time_3 = time.perf_counter()
                distance.damerau_levenshtein_recursive(s1, s2)
                time_4 = time.perf_counter()
                distance.damerau_levenshtein_matrix(s1, s2, False)
                time_5 = time.perf_counter()
                time_l_rec += time_2 - time_1
                time_l_matr += time_3 - time_2
                time_dl_rec += time_4 - time_3
                time_dl_matr += time_5 - time_4
            print()
            print('Levenshtein recursive: {:.7f}'.format(time_l_rec / 100))
            print('Levenshtein matrix: {:.7f}'.format(time_l_matr / 100))
            print('Damerau Levenshtein recursive: {:.7f}'.format(time_dl_rec / 100))
            print('Damerau Levenshtein matrix: {:.7f}'.format(time_dl_matr / 100))

        elif choice == 0:
            break

        else:
            print('Invalid input, try again')
