# Dissertation Projects

## Dataset Retrieval
Here we provide in the `dataset-retrieval` directory the original implementation for retrieval pairs of source and unit test files from github via the sourcegraph API </br>
To skip this step you can use the data.zip provided. This contains a `src` and `test` directory which are used in all the experiments.

## GNN AST experiments
The `test-matcher` directory contains the notebook for transforming the source and unit test files into graphs based on their AST (using the python-graphs library)\n 
and then using these for a graph classification task to match source and unit test file

## TestBERT models
The `TestBERT` and `TestGBERT` directories contain the notebooks used for conducting the code-to-code translation task as outlined in the dissertation\n
The `LongTestBERT` directory contains the untested notebook that could use the Longformer architecture to process whole documents given sufficient compute power
