TEMPLATE = subdirs

CONFIG(debug, debug|release) {
    CONFIGURATION = debug
    SUBDIRS += \
        KNPO_Marenkov \
        Test_choseTheLowestMissingVerts \
        Test_deleteVertAndAllChildrenFromVector \
        Test_detectAllSelectedVerts \
        Test_errorCheck \
        Test_findAllChildren \
        Test_formingAnswerString \
        Test_isGivenSetOfUnderlyingVertsSufficient \
        Test_isGivenSetVertsCoversOverlyingVert \
        Test_isVertContainsInVector \
        Test_readXML
} else {
    CONFIGURATION = release

    SUBDIRS += \
        KNPO_Marenkov
}
