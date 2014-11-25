INCLUDEPATH += \
    ../../Libraries/biopp/bpp-core/src \
    ../../Libraries/biopp/bpp-popgen/src \
    ../../Libraries/biopp/bpp-seq/src

HEADERS += \
    ../../Libraries/biopp/bpp-core/src/Bpp/App/ApplicationTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/App/BppApplication.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/App/NumCalcApplicationTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graph/BasicONode.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graph/BasicTNode.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graph/ONode.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graph/TNode.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graph/UNode.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Fig/XFigGraphicDevice.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Fig/XFigLaTeXFontManager.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Fig/XFigPostscriptFontManager.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Font/Font.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Font/FontManager.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Latex/DvipsColorSet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Latex/PgfGraphicDevice.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Molscript/MolscriptColorSet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/R/RColorSet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Svg/SvgGraphicDevice.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/AbstractGraphicDevice.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/ColorManager.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/ColorSet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/ColorTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/DefaultColorSet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/GraphicDevice.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Point2D.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/Point2DTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Graphics/RgbColor.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/BppODiscreteDistributionFormat.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/BppOParametrizableFormat.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/FileTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/IoDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/IoDiscreteDistributionFactory.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/IoFormat.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/IoParametrizable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Io/OutputStream.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/AbstractNumericalDerivative.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/AbstractOptimizer.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/BfgsMultiDimensions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/BrentOneDimension.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/ConjugateGradientMultiDimensions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/DirectionFunction.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/DownhillSimplexMethod.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/FivePointsNumericalDerivative.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/Functions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/FunctionTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/GoldenSectionSearch.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/MetaOptimizer.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/NewtonBacktrackOneDimension.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/NewtonOneDimension.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/OneDimensionOptimizationTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/OptimizationStopCondition.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/Optimizer.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/PowellMultiDimensions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/ReparametrizationFunctionWrapper.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/SimpleMultiDimensions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/SimpleNewtonMultiDimensions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/ThreePointsNumericalDerivative.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Function/TwoPointsNumericalDerivative.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/AbstractHmmTransitionMatrix.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/AutoCorrelationTransitionMatrix.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/FullHmmTransitionMatrix.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/HmmEmissionProbabilities.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/HmmExceptions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/HmmLikelihood.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/HmmStateAlphabet.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/HmmTransitionMatrix.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/LogsumHmmLikelihood.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/LowMemoryRescaledHmmLikelihood.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Hmm/RescaledHmmLikelihood.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Matrix/EigenValue.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Matrix/LUDecomposition.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Matrix/Matrix.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Matrix/MatrixTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/AbstractDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/BetaDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/ConstantDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/DirichletDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/DiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/ExponentialDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/GammaDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/GaussianDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/InvariantMixedDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/MixtureOfDiscreteDistributions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/MultipleDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/SimpleDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/Simplex.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/TruncatedExponentialDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Prob/UniformDiscreteDistribution.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/ContingencyTableGenerator.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/RandomFactory.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/RandomTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/Uniform01K.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/Uniform01QD.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Random/Uniform01WH.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/Mva/CorrespondenceAnalysis.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/Mva/DualityDiagram.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/Mva/PrincipalComponentAnalysis.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/ContingencyTableTest.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/StatTest.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Stat/StatTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/AbstractParameterAliasable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/AbstractParametrizable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/AdaptiveKernelDensityEstimation.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/AutoParameter.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Constraints.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/DataTable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/DataTableExceptions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Number.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/NumConstants.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/NumTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Parameter.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/ParameterAliasable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/ParameterExceptions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/ParameterList.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Parametrizable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/ParametrizableCollection.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/Range.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/TransformedParameter.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/VectorExceptions.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Numeric/VectorTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Text/KeyvalTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Text/NestedStringTokenizer.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Text/StringTokenizer.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Text/TextTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Utils/AttributesTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Utils/MapTools.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/BppBoolean.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/BppString.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/BppVector.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Clonable.h \
    ../../Libraries/biopp/bpp-core/src/Bpp/Exceptions.h \
    ../../Libraries/biopp/bpp-core/test/PolynomialFunction.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/AbstractIDataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/AbstractODataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/AlleleInfo.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/AnalyzedLoci.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/AnalyzedSequences.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/BasicAlleleInfo.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/BiAlleleMonolocusGenotype.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/DarwinDon.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/DarwinVarSingle.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/DataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/DataSetTools.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Date.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/GeneMapperCsvExport.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Genepop.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/GeneralExceptions.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Genetix.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Group.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/IDataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Individual.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/IODataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/Locality.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/LocusInfo.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MonoAlleleMonolocusGenotype.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MonolocusGenotype.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MonolocusGenotypeTools.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MultiAlleleMonolocusGenotype.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MultilocusGenotype.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MultilocusGenotypeStatistics.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/MultiSeqIndividual.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/ODataSet.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/PolymorphismMultiGContainer.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/PolymorphismMultiGContainerTools.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/PolymorphismSequenceContainer.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/PolymorphismSequenceContainerTools.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/PopgenlibIO.h \
    ../../Libraries/biopp/bpp-popgen/src/Bpp/PopGen/SequenceStatistics.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/AbstractAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/Alphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/AlphabetExceptions.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/AlphabetNumericState.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/AlphabetState.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/AlphabetTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/BinaryAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/CaseMaskedAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/CodonAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/DefaultAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/DNA.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/IntegerAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/LetterAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/NucleicAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/NucleicAlphabetState.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/NumericAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/ProteicAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/ProteicAlphabetState.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/RNA.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/RNY.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Alphabet/WordAlphabet.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAChargeIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAChenGuHuangHydrophobicityIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAChouFasmanAHelixIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAChouFasmanBSheetIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAChouFasmanTurnIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAIndex1Entry.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAIndex2Entry.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAMassIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AASEA1030Index.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AASEAInf10Index.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AASEASup30Index.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AASurfaceIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AAVolumeIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AlphabetIndex1.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/AlphabetIndex2.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/BLOSUM50.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/DefaultNucleotideScore.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/GranthamAAChemicalDistance.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/GranthamAAPolarityIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/GranthamAAVolumeIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/KleinAANetChargeIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/MiyataAAChemicalDistance.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/SimpleIndexDistance.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/SimpleScore.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/AlphabetIndex/UserAlphabetIndex1.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/App/SequenceApplicationTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/AbstractSequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/AlignedSequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/CompressedVectorSiteContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/MapSequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/OrderedSequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SequenceContainerExceptions.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SequenceContainerIterator.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SequenceContainerTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SiteContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SiteContainerExceptions.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SiteContainerIterator.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/SiteContainerTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/VectorSequenceContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Container/VectorSiteContainer.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/AscidianMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/EchinodermMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/GeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/InvertebrateMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/MoldMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/StandardGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/VertebrateMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/GeneticCode/YeastMitochondrialGeneticCode.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/AbstractIAlignment.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/AbstractISequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/AbstractOAlignment.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/AbstractOSequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOAlignmentReaderFormat.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOAlignmentWriterFormat.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOAlphabetIndex1Format.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOAlphabetIndex2Format.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOSequenceReaderFormat.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOSequenceStreamReaderFormat.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/BppOSequenceWriterFormat.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Clustal.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Dcse.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Fasta.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/GenBank.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/IoSequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/IoSequenceFactory.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/IoSequenceStream.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/ISequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/ISequenceStream.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Mase.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/MaseTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/NexusIoSequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/NexusTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/OSequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/OSequenceStream.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/PhredPhd.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/PhredPoly.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Phylip.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/SequenceFileIndex.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/Stockholm.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Io/StreamSequenceIterator.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/CodonSiteTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/DistanceMatrix.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/DNAToRNA.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/NucleicAcidsReplication.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Sequence.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceExceptions.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceIterator.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequencePositionIterators.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceWalker.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceWithAnnotation.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceWithAnnotationTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceWithQuality.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SequenceWithQualityTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Site.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SiteExceptions.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SiteIterator.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SiteTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/StringSequenceTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SymbolList.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/SymbolListTools.h \
    ../../Libraries/biopp/bpp-seq/src/Bpp/Seq/Transliterator.h
