include(macpuffins-wallet.pri)

TEMPLATE = subdirs
CONFIG += ordered

SUBDIRS += wallet

mac {
	QMAKE_INFO_PLIST = wallet/qt/res/Info.plist
}

#MACPUFFINS_CONFIG += Tests

contains( MACPUFFINS_CONFIG, Tests ) {
    SUBDIRS += wallet/test
}

contains( MACPUFFINS_CONFIG, NoWallet ) {
    SUBDIRS += wallet/test
    SUBDIRS -= wallet
}
