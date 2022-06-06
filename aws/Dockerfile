FROM public.ecr.aws/lambda/python:3.9

RUN yum groupinstall -y 'Development Tools' 	

# Install miniconda
ENV CONDA_DIR ~/conda
RUN curl https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh -o ~/miniconda.sh && \
     /bin/bash ~/miniconda.sh -b -p ~/conda

# Put conda in path so we can use conda activate
ENV PATH=$CONDA_DIR/bin:$PATH

# Install the function's dependencies using file requirements.txt
# from your project folder.

RUN rm -rf /var/lang/
COPY aws/requirements.yml  .
RUN conda install -c conda-forge mamba
RUN mamba env create --file requirements.yml --prefix /var/lang 

# Copy function code
COPY aws/lambda_function.py ${LAMBDA_TASK_ROOT}

RUN mkdir /root/repo 
COPY . /root/repo/

COPY CMakeLists.txt /root/repo/
RUN cd /root/repo && \
    mkdir -p build && \
    cd build &&  cmake /root/repo -DCMAKE_INSTALL_PREFIX=/var/lang/ -DSPICEQL_BUILD_DOCS=NO -DSPICEQL_BUILD_TESTS=NO && \
    make install
RUN cd /root/repo/build/bindings/python/ && python setup.py install 

# Set the CMD to your handler (could also be done as a parameter override outside of the Dockerfile)
CMD [ "lambda_function.lambda_handler" ]
