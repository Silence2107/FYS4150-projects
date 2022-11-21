
# builds energy histogram based on data in a provided file

import pandas as pd
import matplotlib.pyplot as plt
import argparse

import ROOT

# parse command line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--temperature', help='temperature in J/kB units')
parser.add_argument('--fileprefix', help='path prefix to a file containing energy data')

args = parser.parse_args()

# read data from file
data = pd.read_csv('{}{}_data.txt'.format(
    args.fileprefix, args.temperature), sep=' ')

# build histogram
canvas = ROOT.TCanvas('c', 'c')
hist = ROOT.TH1D('h', 'Energy Histogram', 50, -1.997, -1.992)

# fill histogram
for i in range(len(data)):
    hist.Fill(float(data['energyPerSite'][i]))
hist.Scale(1.0 / hist.Integral()) # normalize by counts

# fit with gaussian
import numpy as np
param_array = np.array([0.0, 0.0, 0.0])
gauss = ROOT.TF1('gauss', '[0]*exp(-0.5*((x-[1])/[2])**2)', -1.997, -1.992)
gauss.SetParameters(0.15, -1.998, 0.01)
hist.Fit(gauss, 'R')
gauss.GetParameters(param_array)

# visuals
from ROOT import gPad, gStyle
gPad.SetTicks()
gPad.SetTopMargin(0.05)
gPad.SetLeftMargin(0.11)
gPad.SetRightMargin(0.05)
gPad.SetBottomMargin(0.1)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
legend = ROOT.TLegend(0.4, 0.7, 0.88, 0.92)
legend.SetBorderSize(0)
legend.SetTextFont(43)
legend.SetTextSize(22)
legend.SetFillStyle(0)
legend.SetMargin(0.35)
legend.SetHeader('#splitline{Ising 2D, energy distr.}{for T = ' + args.temperature + ' J/k_{B}}')
legend.AddEntry(hist, 'MC, 1000x10000 runs', 'l')
legend.AddEntry(gauss, 'Gaussian fit, #sigma = {0:.2E}'.format(param_array[2]), 'l')
hist.SetLineWidth(2)
hist.GetYaxis().SetLabelFont(43)
hist.GetYaxis().SetLabelSize(20)
hist.GetYaxis().SetTitleFont(43)
hist.GetYaxis().SetTitleSize(20)
hist.GetYaxis().SetTitleOffset(1.1)
hist.GetXaxis().SetLabelFont(43)
hist.GetXaxis().SetLabelSize(20)
hist.GetXaxis().SetTitleFont(43)
hist.GetXaxis().SetTitleSize(20)
hist.GetXaxis().SetTitleOffset(1.1)
hist.GetXaxis().SetTitle('Energy per site, rel.u.')
hist.GetYaxis().SetTitle('Counts normalized')
#hist.GetXaxis().SetLimits(-2.0, -1.99)
hist.SetLineWidth(2)
hist.SetLineColor(1)
#less points on x axis
hist.GetXaxis().SetNdivisions(505)


# draw histogram
hist.Draw('HIST E')
gauss.Draw('C SAME')
legend.Draw()

# save histogram
canvas.SaveAs('{}{}_energyPerSite.pdf'.format(
    args.fileprefix, args.temperature))

"""
# builds energy histogram based on data in a provided file

import pandas as pd
import matplotlib.pyplot as plt
import argparse

import ROOT

# parse command line arguments
parser = argparse.ArgumentParser()
parser.add_argument('--temperature', help='temperature in J/kB units')
parser.add_argument(
    '--fileprefix', help='path prefix to a file containing energy data')

args = parser.parse_args()

# read data from file
data = pd.read_csv('{}{}_data.txt'.format(
    args.fileprefix, args.temperature), sep=' ')

# build histogram
canvas = ROOT.TCanvas('c', 'c')
hist = ROOT.TH1D('h', 'Energy Histogram', 50, -1.26, -1.16)

# fill histogram
for i in range(len(data)):
    hist.Fill(float(data['energyPerSite'][i]))
hist.Scale(1.0 / hist.Integral())  # normalize by counts

# fit with gaussian
import numpy as np
param_array = np.array([0.0, 0.0, 0.0])
gauss = ROOT.TF1('gauss', '[0]*exp(-0.5*((x-[1])/[2])**2)', -1.26, -1.21)
gauss.SetParameters(0.15, -1.235, 0.05)
hist.Fit(gauss, 'R')
gauss.GetParameters(param_array)

# visuals
from ROOT import gPad, gStyle
gPad.SetTicks()
gPad.SetTopMargin(0.05)
gPad.SetLeftMargin(0.11)
gPad.SetRightMargin(0.05)
gPad.SetBottomMargin(0.1)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
legend = ROOT.TLegend(0.4, 0.7, 0.88, 0.92)
legend.SetBorderSize(0)
legend.SetTextFont(43)
legend.SetTextSize(22)
legend.SetFillStyle(0)
legend.SetMargin(0.35)
legend.SetHeader(
    '#splitline{Ising 2D, energy distr.}{for T = ' + args.temperature + ' J/k_{B}}')
legend.AddEntry(hist, 'MC, 1000x10000 runs', 'l')
legend.AddEntry(
    gauss, 'Gaussian fit, #sigma = {0:.2E}'.format(param_array[2]), 'l')
hist.SetLineWidth(2)
hist.GetYaxis().SetLabelFont(43)
hist.GetYaxis().SetLabelSize(20)
hist.GetYaxis().SetTitleFont(43)
hist.GetYaxis().SetTitleSize(20)
hist.GetYaxis().SetTitleOffset(1.1)
hist.GetXaxis().SetLabelFont(43)
hist.GetXaxis().SetLabelSize(20)
hist.GetXaxis().SetTitleFont(43)
hist.GetXaxis().SetTitleSize(20)
hist.GetXaxis().SetTitleOffset(1.1)
hist.GetXaxis().SetTitle('Energy per site, rel.u.')
hist.GetYaxis().SetTitle('Counts normalized')
#hist.GetXaxis().SetLimits(-2.0, -1.99)
hist.SetLineWidth(2)
hist.SetLineColor(1)
#less points on x axis
hist.GetXaxis().SetNdivisions(505)


# draw histogram
hist.Draw('HIST E')
gauss.Draw('C SAME')
legend.Draw()

# save histogram
canvas.SaveAs('{}{}_energyPerSite.pdf'.format(
    args.fileprefix, args.temperature))
"""