# Set the source group name
SET(GROUP MOLMEC/AMBER)

# List all filenames of this group here
SET(SOURCES_LIST
	amber.C
	amberBend.C
	amberNonBonded.C
	amberStretch.C
	amberTorsion.C
	GAFFCESParser.C
	GAFFTypeProcessor.C
)

SET(PARSER_LEXER_LIST
	GAFFCESParser
)

#ADD_BALL_PARSER_LEXER("MOLMEC/AMBER" "GAFFCESParser" "GAFFCESParser")
