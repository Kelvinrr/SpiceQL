#include <vector>
#include <ghc/fs_std.hpp>


// paths for testing base / shared kernel queries
std::vector<fs::path> base_paths = {
    "/isis_data/base/kernels/sclk/naif0001.tls",
    "/isis_data/base/kernels/sclk/naif0002.tls",
    "/kernels/pck/pck00006.tpc"
};

// paths for testing messenger kernel queries
std::vector<fs::path> mess_paths = {
    "/isis_data/messenger/kernels/ck/msgr_1234_v01.bc",
    "/isis_data/messenger/kernels/ck/msgr_1235_v01.bc",
    "/isis_data/messenger/kernels/ck/msgr_1235_v02.bc",
    "/isis_data/messenger/kernels/ck/msgr_1236_v03.bc",
    "/isis_data/messenger/kernels/sclk/messenger_0001.tsc",
    "/isis_data/messenger/kernels/sclk/messenger_0002.tsc",
    "/isis_data/messenger/kernels/spk/msgr_20040803_20150328_od360sc_0.bsp",
    "/isis_data/messenger/kernels/spk/msgr_20040803_20150328_od346sc_0.bsp",
    "/isis_data/messenger/kernels/fk/msgr_v001.tf",
    "/isis_data/messenger/kernels/fk/msgr_v002.tf",
    "/isis_data/messenger/kernels/iak/mdisAddendum001.ti",
    "/isis_data/messenger/kernels/iak/mdisAddendum002.ti",
    "/isis_data/messenger/kernels/ik/msgr_mdis_v001.ti",
    "/isis_data/messenger/kernels/ik/msgr_mdis_v002.ti",
    "/isis_data/messenger/kernels/pck/pck00010_msgr_v02.tpc",
    "/isis_data/messenger/kernels/pck/pck00010_msgr_v03.tpc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc332211_112233_sub_v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc332211_445566_sub_v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc332211_445566_sub_v2.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc665544_445566_sub_v2.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc3322_usgs_v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc3322_usgs_v2.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc1122_usgs_v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_sc0001_usgs_v3.bc",
    "/isis_data/messenger/kernels/ck/messenger_1122_v01.bc",
    "/isis_data/messenger/kernels/ck/messenger_3344_v01.bc",
    "/isis_data/messenger/kernels/ck/messenger_3344_v02.bc",
    "/isis_data/messenger/kernels/ck/messenger_5566_v03.bc",
    "/isis_data/messenger/kernels/tspk/de423s.bsp",
    "/isis_data/messenger/kernels/tspk/de405.bsp",
    "/isis_data/messenger/kernels/ck/msgr_mdis_gm332211_112233v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_gm332211_112233v2.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_gm012345_112233v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_gm332211_999999v1.bc",
    "/isis_data/messenger/kernels/ck/msgr_mdis_gm012345_999999v2.bc"
};

// paths for testing clementine kernel queries
std::vector<fs::path> clem1_paths = {
    "/isis_data/clementine1/kernels/ck/clem_123.bck",
    "/isis_data/clementine1/kernels/ck/clem_124.bck",
    "/isis_data/clementine1/kernels/ck/clem_125.bck",
    "/isis_data/clementine1/kernels/ck/clem_126.bck",

    "/isis_data/clementine1/kernels/ck/clem_ulcn2005_6hr.bc",

    "/isis_data/clementine1/kernels/sclk/dspse001.tsc",
    "/isis_data/clementine1/kernels/sclk/dspse002.tsc",

    "/isis_data/clementine1/kernels/spk/clem_123_v01.bsp",
    "/isis_data/clementine1/kernels/spk/clem_124_v01.bsp",

    "/isis_data/clementine1/kernels/fk/clem_v01.tf",

    "/isis_data/clementine1/kernels/ik/clem_uvvis_beta_ik_v04.ti",

    "/isis_data/clementine1/kernels/iak/uvvisAddendum001.ti",
    "/isis_data/clementine1/kernels/iak/uvvisAddendum002.ti",
    "/isis_data/clementine1/kernels/iak/nirAddendum001.ti",
    "/isis_data/clementine1/kernels/iak/nirAddendum002.ti"
};


std::vector<fs::path> galileo_paths = {
    "/isis_data/galileo/kernels/ck/ck90342a_plt.bc",
    "/isis_data/galileo/kernels/ck/ck90342b_plt.bc",
    "/isis_data/galileo/kernels/ck/ck90343a_plt.bc",
    "/isis_data/galileo/kernels/ck/CKmerge_type3.plt.bck",

    "/isis_data/galileo/kernels/ck/galssi_cal_med.bck",
    "/isis_data/galileo/kernels/ck/galssi_eur_usgs2020.bc",
    "/isis_data/galileo/kernels/ck/galssi_io_iau010806baa.bck",

    "/isis_data/galileo/kernels/sclk/mk00062b.tsc",

    "/isis_data/galileo/kernels/spk/s000131a.bsp",
    "/isis_data/galileo/kernels/spk/s000407a.bsp",

    "/isis_data/galileo/kernels/iak/ssiAddendum001.ti",

    "/isis_data/galileo/kernels/pck/pck00010_msgr_v23_europa2020.tpc"
};
