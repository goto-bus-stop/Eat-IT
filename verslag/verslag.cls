\LoadClass[a4paper,11pt]{article}

\RequirePackage{graphicx}
\RequirePackage[dutch]{babel}
\RequirePackage{tocloft}
\RequirePackage{hyperref}
\RequirePackage[utf8]{inputenc}


\setcounter{secnumdepth}{0}




%----------------------------------------------------------------------------------------
%   TITEL PAGINA
%----------------------------------------------------------------------------------------

\newcommand*{\titelpagina}{\begingroup % Maak het commando om de titel in het document op te nemen
\pagenumbering{gobble}
\begin{minipage}[t]{0.2\textwidth}\
\raisebox{-.7\textheight}{\includegraphics[height=\textwidth, angle=90]{logo}}
\end{minipage}%
\begin{minipage}[t]{0.79\textwidth}
\hbox{
\hspace*{0.01\textwidth} 

\hspace*{0.05\textwidth}
\parbox[t]{0.8\textwidth}{

{\noindent\Huge\bfseries  Plan van Aanpak}\\[2\baselineskip] % Titel
{\noindent\Huge\bfseries plusproject eatIT}\\[4\baselineskip] % Ondertitel of beschrijving
{\Large \textsc{Marijn Pool}}\\ % Auteur
{\large \textit{338021}} \\% Studentnummer

{\Large \textsc{René Kooi}}\\ % Auteur
{\large \textit{337805}} % Studentnummer

\vspace{0.5\textheight} % Witruimte tussen het titelblok en de verslaginfo
{\noindent Docent: Henkjan Hekman  \& Ronald van Dijk}\\ % Docent
{\noindent Thema 1.1 - Werken met Databases 2014-2015}\\
{\noindent Datum: \today}\\
}}
\end{minipage}%
\clearpage
\setcounter{page}{1}    
\endgroup}

%----------------------------------------------------------------------------------------
%   INHOUDSOPGAVE
%----------------------------------------------------------------------------------------
\newcommand*{\inhoudsopgave}{\begingroup
\pagenumbering{arabic}
\tableofcontents
\clearpage
\endgroup}