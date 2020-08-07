import RdToMd
import MdManager

MAIN_PATH = "/mnt/6DFB625670EDD9C2/develop/R/GCATR/man/"
REDME_PATH = "/mnt/6DFB625670EDD9C2/develop/R/GCATR/README.md"

def __main__():

    print("Start R-Doc to Readme")

    b = MdManager.MdManager(REDME_PATH, MAIN_PATH)
    print(b.start())

    print("End!!")


__main__()