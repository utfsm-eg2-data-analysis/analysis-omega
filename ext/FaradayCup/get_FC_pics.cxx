TNtuple *t = new TNtuple("t","tuple","run:FC");
t->ReadFile("FCup_g2_1e-10C_C-thickD2rn.txt");
t->Draw("FC*1e-10:run");
TH1F *h = (TH1F*) gROOT->FindObject("htemp");
h->SetTitle("Faraday Cup Integrated Current / C-thickD2");
h->GetYaxis()->SetTitleOffset(1.1);
h->GetYaxis()->SetTitle("FCup_g2 (live gated) C");
c1->GetPad(0)->SetRightMargin(0.05);
c1->GetPad(0)->SetLeftMargin(0.14);
c1->SaveAs("FCup_CD2.gif");
c1->SaveAs("FCup_CD2.C");


TNtuple *t = new TNtuple("t","tuple","run:FC");
t->ReadFile("FCup_g2_1e-10C_Fe-thickD2rn.txt");
t->Draw("FC*1e-10:run");
TH1F *h = (TH1F*) gROOT->FindObject("htemp");
h->SetTitle("Faraday Cup Integrated Current / Fe-thickD2");
h->GetYaxis()->SetTitleOffset(1.1);
h->GetYaxis()->SetTitle("FCup_g2 (live gated) C");
c1->GetPad(0)->SetRightMargin(0.05);
c1->GetPad(0)->SetLeftMargin(0.14);
c1->SaveAs("FCup_FeD2.gif");
c1->SaveAs("FCup_FeD2.C");

TNtuple *t = new TNtuple("t","tuple","run:FC");
t->ReadFile("FCup_g2_1e-10C_Pb-thinD2rn.txt");
t->Draw("FC*1e-10:run");
TH1F *h = (TH1F*) gROOT->FindObject("htemp");
h->SetTitle("Faraday Cup Integrated Current / Pb-thinD2");
h->GetYaxis()->SetTitleOffset(1.1);
h->GetYaxis()->SetTitle("FCup_g2 (live gated) C");
c1->GetPad(0)->SetRightMargin(0.05);
c1->GetPad(0)->SetLeftMargin(0.14);
c1->SaveAs("FCup_PbD2.gif");
c1->SaveAs("FCup_PbD2.C");


TNtuple *t = new TNtuple("t","tuple","run:FC");
t->ReadFile("FCup_g2_1e-10C_all.txt");
t->Draw("FC*1e-10:run");
TH1F *h = (TH1F*) gROOT->FindObject("htemp");
h->SetTitle("Faraday Cup Integrated Current / all");
h->GetYaxis()->SetTitleOffset(1.1);
h->GetYaxis()->SetTitle("FCup_g2 (live gated) C");
c1->GetPad(0)->SetRightMargin(0.05);
c1->GetPad(0)->SetLeftMargin(0.14);
c1->SaveAs("FCup_all.gif");
c1->SaveAs("FCup_all.C");
