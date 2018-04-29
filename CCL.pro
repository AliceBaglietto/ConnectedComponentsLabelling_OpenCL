###
###  @author Alice Baglietto
###  @version 1.0
###  @date 4 May 2018
###
###  @file CCL.pro
###  @brief This is where the whole implementation of the project is put together:
###         Stores GPU library, CPU library and application file.

TEMPLATE = subdirs
SUBDIRS = CCL_gpu CCL_cpu application
OTHER_FILES += $$PWD/images/*.png \
                $$PWD/README.txt

