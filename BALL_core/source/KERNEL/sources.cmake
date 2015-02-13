# Set the source group name
SET(GROUP KERNEL)

# List all filenames of this group here
SET(SOURCES_LIST
	atom.C
	atomContainer.C
	bond.C
	chain.C
	expression.C
	expressionParser.C
	expressionPredicate.C
	expressionTree.C
	extractors.C
	fragment.C
	global.C
	molecularInteractions.C
	molecule.C
	nucleicAcid.C
	nucleotide.C
	PDBAtom.C
	predicate.C
	protein.C
	PTE.C
	residue.C
	secondaryStructure.C
	selector.C
	standardPredicates.C
	system.C
)

SET(PARSER_LEXER_LIST
	expressionParser
)
