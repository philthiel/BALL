#new_header#


# --------------------------------------------------------------------------
# BALL core dependencies
#
set(TMP_DEP_LIBS)
set(TMP_DEP_MISSING)

# Mandatory dependencies
include(config_external/ball_boost)
include(config_external/ball_eigen3)
include(config_external/ball_flexbison)
include(config_external/ball_qt)

# Optional dependencies
include(config_external/ball_fftw)
include(config_external/ball_lpsolve)
include(config_external/ball_mpi)
include(config_external/ball_openbabel)
include(config_external/ball_tbb)
include(config_external/ball_xdr)

set(BALL_DEP_LIBS ${TMP_DEP_LIBS})
set(BALL_DEP_MISSING ${TMP_DEP_MISSING})
list(REMOVE_DUPLICATES BALL_DEP_LIBS)

# --------------------------------------------------------------------------
# BALL view dependencies
#
set(TMP_DEP_LIBS)
set(TMP_DEP_MISSING)

# Mandatory dependencies
include(config_external/ball_boost)
include(config_external/ball_qt)

# Optional dependencies
include(config_external/ball_cuda)
include(config_external/ball_tbb)
include(config_external/ball_xdr)

set(VIEW_DEP_LIBS ${TMP_DEP_LIBS})
set(VIEW_DEP_MISSING ${TMP_DEP_MISSING})
list(REMOVE_DUPLICATES VIEW_DEP_LIBS)
