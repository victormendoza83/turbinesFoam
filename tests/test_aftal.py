#!/usr/bin/env python
"""Tests for `axialFlowTurbineALSource`."""

from __future__ import division, print_function
import subprocess
import pandas as pd
import os
import numpy as np


def setup():
    os.chdir("axialFlowTurbineALSource")
    out = subprocess.check_output("./getTutorialFiles.sh", shell=True)


def check_created():
    """Test that axialFlowTurbineALSource was created."""
    txt = "Selecting finite volume options model type axialFlowTurbineALSource"
    subprocess.check_output(["grep", txt, "log.pimpleFoam"])


def check_perf(angle0=540.0):
    """Test AFTAL performance was written and in reasonable range."""
    df = pd.read_csv("postProcessing/turbines/0/turbine.csv")
    df = df.drop_duplicates("time", keep="last")
    if df.angle_deg.max() < angle0:
        angle0 = 0.0
    mean_tsr = df.tsr[df.angle_deg >= angle0].mean()
    mean_cp = df.cp[df.angle_deg >= angle0].mean()
    mean_cd = df.cd[df.angle_deg >= angle0].mean()
    print("Performance from {:.1f}--{:.1f} degrees:".format(angle0,
          df.angle_deg.max()))
    print("Mean TSR = {:.2f}".format(mean_tsr))
    print("Mean C_P = {:.2f}".format(mean_cp))
    print("Mean C_D = {:.2f}".format(mean_cd))
    assert mean_tsr == 6.0
    assert 0.4 < mean_cp < 1.0
    assert 0.5 < mean_cd < 1.0


def test_serial():
    """Test axialFlowTurbineALSource in serial."""
    output_clean = subprocess.check_output("./Allclean")
    try:
        output_run = subprocess.check_output("./Allrun")
    except subprocess.CalledProcessError:
        print(subprocess.check_output(["tail", "-n", "200",
                                       "log.pimpleFoam"]).decode())
        assert False
    check_created()
    check_perf()
    log_end = subprocess.check_output(["tail", "log.pimpleFoam"]).decode()
    print(log_end)
    assert log_end.split()[-1] == "End"


def test_parallel():
    """Test axialFlowTurbineALSource in parallel."""
    output_clean = subprocess.check_output("./Allclean")
    try:
        output_run = subprocess.check_output(["./Allrun", "-parallel"])
    except subprocess.CalledProcessError:
        print(subprocess.check_output(["tail", "-n", "200",
                                       "log.pimpleFoam"]).decode())
        assert False
    check_created()
    check_perf()
    log_end = subprocess.check_output(["tail", "log.pimpleFoam"]).decode()
    print(log_end)
    assert "Finalising parallel run" in log_end


def teardown():
    """Move back into tests directory."""
    os.chdir("../")
