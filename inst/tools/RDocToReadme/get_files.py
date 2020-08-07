import RdToMd
import MdManager

MAIN_PATH = "/mnt/6DFB625670EDD9C2/develop/R/GCATR/man/"


def __main__():

    print("Find R-Doc")

    b = MdManager.MdManager("", MAIN_PATH)
    print(b.get_list())

    print("End!!")


__main__()