#!/bin/bash
docker run --rm zyclonite/sysbench --num-threads=16 --test=fileio --file-total-size=3G --time=30 --file-test-mode=seqrewr prepare
docker run --rm zyclonite/sysbench --num-threads=16 --test=fileio --file-total-size=3G --time=30 --file-test-mode=seqrewr run
docker run --rm zyclonite/sysbench --num-threads=16 --test=fileio --file-total-size=3G --time=30 --file-test-mode=seqrewr cleanup
