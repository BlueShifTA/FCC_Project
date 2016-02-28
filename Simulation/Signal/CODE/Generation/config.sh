#!/bin/sh
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/usr/local/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib
fi
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF
fi
export LHAPATH=/home/orion/Software/LHAPDF/../../../share/lhapdf/PDFsets
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF
fi
export LHAPATH=/home/orion/Software/LHAPDF/share/lhapdf/PDFsets
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF
fi
export LHAPATH=/home/orion/Software/LHAPDF/../../../share/lhapdf/PDFsets
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF
fi
export LHAPATH=/home/orion/Software/LHAPDF/share/lhapdf/PDFsets
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF/lib
fi
export LHAPATH=/home/orion/Software/LHAPDF/share/lhapdf/PDFsets
if [ ! $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=/home/orion/Software/LHAPDF/lib
fi
if [ $?LD_LIBRARY_PATH ]; then
  export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/home/orion/Software/LHAPDF/lib
fi
export LHAPATH=/home/orion/Software/LHAPDF/share/lhapdf/PDFsets
