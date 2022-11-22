
import ROOT
from ROOT import gPad, gStyle

import pandas as pd
import numpy as np

# import a few csv files
grids = [20, 30, 40, 50, 60, 80, 100]
data = []
for l in grids:
    data.append(pd.read_csv(
        'cv_T_L{}_fine.csv'.format(l), sep=',', names=['T', 'Cv']))

# build tgraphs out of the data
graphs = []
for i in range(len(data)):
    graph = ROOT.TGraph(len(data[i]['T']), np.array(data[i]['T']), np.array(data[i]['Cv']))
    graph.SetTitle('L = {}'.format(grids[i]))
    graph.SetMarkerStyle(20+i)
    graph.SetMarkerSize(1.0)
    graph.SetMarkerColor(i+1)
    graph.SetLineColor(i+1)

    graphs.append(graph)

# build a canvas
canvas = ROOT.TCanvas('c', 'c')

# multigraph
mg = ROOT.TMultiGraph()
for graph in graphs:
    mg.Add(graph, '2CP')
mg.GetYaxis().SetLabelFont(43)
mg.GetYaxis().SetLabelSize(20)
mg.GetYaxis().SetTitleFont(43)
mg.GetYaxis().SetTitleSize(20)
mg.GetYaxis().SetTitleOffset(1.1)
mg.GetXaxis().SetLabelFont(43)
mg.GetXaxis().SetLabelSize(20)
mg.GetXaxis().SetTitleFont(43)
mg.GetXaxis().SetTitleSize(20)
mg.GetXaxis().SetTitleOffset(1.1)
mg.GetXaxis().SetNdivisions(1010)

# legend
gPad.SetTicks()
gPad.SetTopMargin(0.05)
gPad.SetLeftMargin(0.11)
gPad.SetRightMargin(0.05)
gPad.SetBottomMargin(0.1)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
legend = ROOT.TLegend(0.6, 0.6, 0.9, 0.9)
legend.SetNColumns(2)
legend.SetBorderSize(0)
legend.SetTextFont(43)
legend.SetTextSize(22)
legend.SetFillStyle(0)
legend.SetMargin(0.35)
legend.SetHeader(
    '#splitline{Ising 2D, temp. scans}{for various lattice sizes}')
#set align
legend.SetTextAlign(21)
for graph in graphs:
    legend.AddEntry(graph, graph.GetTitle(), 'LP')

# drawing
mg.Draw('AXIS')
mg.GetXaxis().SetTitle('T, J/k_{B}')
mg.GetYaxis().SetTitle('C_{v}, k_{B}')

legend.Draw()

canvas.SaveAs('Cv_shift.pdf')
#clean up
canvas.Close()
canvas = ROOT.TCanvas('c2', 'c2')

# fit the data with general gaussian function 
# and store the mean and its error
means = []
mean_errors = []
for i in range(len(data)):
    fit = ROOT.TF1('fit', '[0]*exp(-0.5*((x-[1])/[2])**2)', graphs[i].GetX()[0], graphs[i].GetX()[graphs[i].GetN()-1])
    fit.SetParameters(0.15, 2.28, 0.1)
    graphs[i].Fit(fit, 'R')
    means.append(fit.GetParameter(1))
    mean_errors.append(fit.GetParError(1))

# build a new TGraphErrors out of these means
graph = ROOT.TGraphErrors(len(means), 1 / np.array(grids), np.array(means), np.zeros(len(means)), np.array(mean_errors))
graph.GetYaxis().SetLabelFont(43)
graph.GetYaxis().SetLabelSize(20)
graph.GetYaxis().SetTitleFont(43)
graph.GetYaxis().SetTitleSize(20)
graph.GetYaxis().SetTitleOffset(1.1)
graph.GetXaxis().SetLabelFont(43)
graph.GetXaxis().SetLabelSize(20)
graph.GetXaxis().SetTitleFont(43)
graph.GetXaxis().SetTitleSize(20)
graph.GetXaxis().SetTitleOffset(1.1)
#graph.GetXaxis().SetNdivisions(1010)
graph.GetXaxis().SetTitle('L^{-1}')
graph.GetYaxis().SetTitle('T_{c}(L), J/k_{B}')

# fit the data with a linear function, excluding first point
fit = ROOT.TF1('fit', '[0] + [1]*x', 1 / grids[0], 1 / grids[-2])
fit.SetParameters(2.3, 0.1)
graph.Fit(fit, 'R')

# legend
gPad.SetTicks()
gPad.SetTopMargin(0.05)
gPad.SetLeftMargin(0.11)
gPad.SetRightMargin(0.05)
gPad.SetBottomMargin(0.1)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
legend = ROOT.TLegend(0.2, 0.6, 0.5, 0.9)
legend.SetBorderSize(0)
legend.SetTextFont(43)
legend.SetTextSize(22)
legend.SetFillStyle(0)
legend.SetMargin(0.35)
legend.SetHeader(
    'Ising 2D, temp. scaling, fit-based')
legend.AddEntry(graph, 'gaussian means', 'LP')
legend.AddEntry(fit, 'linear fit', 'L')
# drawing
graph.Draw('AP')
legend.Draw()

canvas.SaveAs('Cv_shift_fit.pdf')