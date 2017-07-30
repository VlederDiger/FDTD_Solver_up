# -*- coding: utf-8 -*-
from .helpers.waveguide import check_point as check_point_core
from .helpers.waveguide_shell import check_point as check_point_shell
from .helpers.output import output_array_to_file

import argparse
import math


def write_eps(x_0, y_0, length, d, alpha, size_x, size_y, n_core):
    eps = []
    print('Start processing epsilon')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_core(x - x_0, y - y_0, d, length, alpha):
                eps.append(n_core)
            else:
                eps.append(1)
    print('Finish processing epsilon')
    output_array_to_file(eps, 'epsilon.txt', size_x)


def write_sig(x_0, y_0, length, d, d_shell, size_x, size_y, sig_shell):
    sig = []
    print('Start processing sigma')
    for y in range(size_y):
        print('Processing [{}/{}]'.format(y, size_y - 1), end="\r")
        for x in range(size_x):
            if check_point_shell(x - x_0, y - y_0, d, d_shell, length):
                sig.append(sig_shell)
            else:
                sig.append(0)
    print('Finish processing sigma')
    output_array_to_file(sig, 'sigma.txt', size_x)


def write(lam_px, n_core, sig_shell, d_over_lam, alpha):
    length = int(15 * lam_px)
    d_shell = int(d_over_lam * lam_px + 8 * lam_px)
    size_x = int(26 * lam_px + length)
    size_y = int(10 * lam_px + d_shell)
    x_0 = int(11 * lam_px)
    y_0 = int(size_y / 2)
    write_eps(x_0, y_0, length, d_over_lam * lam_px, alpha, size_x, size_y, n_core)
    write_sig(x_0, y_0, length, d_over_lam * lam_px, d_shell, size_x, size_y, sig_shell)

if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("--lam_px", help="Number of pixels per wavelength")
    parser.add_argument("--n_core", help="Refractive index of waveguide core")
    parser.add_argument("--sig_shell", help="Sigma of waveguide shell")
    parser.add_argument("--d_lam", help="Waveguide diameter in lambda")
    parser.add_argument("--alpha", help="Cone angle in degrees")
    args = parser.parse_args()
    lam_px = int(args.lam_px)
    n_core = float(args.n_core)
    sig_shell = float(args.sig_shell)
    d_lam = float(args.d_lam)
    alpha = float(args.alpha) / 180.0 * math.pi
    write(lam_px, n_core, sig_shell, d_lam, alpha)