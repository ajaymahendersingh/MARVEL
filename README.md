# py2c_riscv_fpga
This repository is a collection of python notebooks that can be used to generate C test cases from a high-level python code using TVM. The generated C code is generic and can be compiled for any target.

# Setup
We will use MobileNetV1 as an example. However, the process described in this tutorial is suitable for use with a variety of different models (see src/ folder).

MobileNetV1 is a convolutional neural network which takes 224×224 images as inputs and classifies them into one of a thousand different categories. We will use transfer learning to train the networks which will classify images as one of two possible categories: 'car' or 'not car'. Furthermore, the model will be updated to take images of sizes 64×64 as inputs. This will help reduce the size of the model.

A labeled dataset of 8,144 'cars' images can be downloaded from DeepAI and a labeled dataset of 5,000 'not cars' images can be downloaded from COCO Datasets. The Jupyter Notebook provided will perform this step, although it may take several minutes. Once this dataset is downloaded, each of the images must be resized to 64×64. This is achieved using Tensorflow Keras utility.

# Training the model
Before training this model, the available data is split into two partitions: training and testing. 80% of the samples are used for training, with the remaining 20% being used for validation. The Tensorflow package comes with a generic pretrained MobileNetV1 model. We will use this model as a starting point and use transfer learning to retrain the model for our specific task: recognising cars. This model is downloaded through the provided Jupyter Notebook. This generic model then has its last 5 layers removed and replaced with 5 layers tailored to this task. This task specific model is then trained on the labeled training data that was downloaded.

# Reducing model size for embedded applications
We now have a trained TensorFlow model based on the MobileNetV1 model which fits our specific task. However, this model is still far too large to fit in the limited program memory available on an embedded device. This model has 216,000 parameters and each parameter is represented as a 32-bit floating point number. In order to reduce the program size, we will quantise the model parameters to 8-bit integers. This can be done automatically with the TensorFlow package, as is shown in the Jupyter notebook.

# TVM: Python model to bare-metal C
Up until this point, we have been concerned with using TensorFlow to generate a suitable neural network model. We now have a suitable model in Python, but must convert this model to C source code for use by the Synopsys ASIP Designer toolset. This is achieved using the TVM machine learning compiler. This compiler generates C code from high-level Python models tailored for a specific target. In our case, the target we are using does not have an operating system and is a RISC-V processor. For this reason, we specify the target simply as 'C'. This generates baremetal-optimised, processor-agnostic C code. We must also disable vectorisation, as this is also not supported by our processor. The Python commands to achieve this are included in the Jupyter Notebook.

