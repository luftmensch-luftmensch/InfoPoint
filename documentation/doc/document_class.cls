% TeX root = main.tex
\NeedsTeXFormat{LaTeX2e}
\ProvidesClass{document_class}[2022/06/01 Document Class]
\LoadClass[10pt]{extreport}

% Requirements
\RequirePackage{xcolor}											% Colores
\RequirePackage{graphicx}										% Load images
\RequirePackage{geometry}										% Page layout
\RequirePackage{tikz}												% Drawings
\RequirePackage{afterpage}									% Macro to run after the page has ended
\RequirePackage[compatV3]{fancyhdr}					% Page headers and footers
\RequirePackage[no-math]{fontspec}					% font family
\RequirePackage[explicit]{titlesec}					% Change document style
\RequirePackage{titletoc}										% Change document style
\RequirePackage{etoolbox}										% Patch environments
\RequirePackage[italian]{babel}							% Change document lang to it
\RequirePackage{hyphenat}										% Hypernat words that requires to
\RequirePackage{parskip}										% Change parskip/parindent
\RequirePackage
	{listings, lstautogobble, lstfiracode}		% lstlisting for code, autogobble and firacode for good looking
\RequirePackage{hyperref}										% Add urls
\RequirePackage{amsmath,amssymb, fdsymbol}	% Symbols
\RequirePackage{enumitem}										% Customize itemize/enumerate envs
\RequirePackage{calc}												% latex calculations

% Macros
\newcommand\blankpage
	{\null\thispagestyle{empty}\addtocounter{page}{-1}\newpage}

% Define colors
\definecolor{orange}{HTML}{FF9507}
\definecolor{blue}{HTML}{179AFF}
\definecolor{sapphire}{HTML}{2B50AA}
\definecolor{cherryred}{HTML}{FF004D}
\definecolor{turquoise}{HTML}{00F5CC}
\definecolor{seagreen}{HTML}{22AAA1}
\definecolor{green}{HTML}{17FF7C}
\definecolor{red}{HTML}{FF3E4B}
\definecolor{yellow}{HTML}{DBED00}
\definecolor{naplesyellow}{HTML}{FFDF64}
\definecolor{violet}{HTML}{47007D}
\definecolor{pink}{HTML}{FF69B4}
\definecolor{neutral}{HTML}{888888}

% Define icons
% TODO: Add icons
\makeatletter
	\newfontfamily\IcoMoon{IcoMoon}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
	]	

	\def\inumber{{\IcoMoon\char"E918}}
	\def\inumbernegative{{\IcoMoon\char"E919}}
	\def\itick{{\IcoMoon\char"E915}}
	\def\icross{{\IcoMoon\char"E916}}
	\def\ihome{{\IcoMoon\char"E914}}
	\def\ifolder{{\IcoMoon\char"E92F}}
	\def\iquotel{{\IcoMoon\char"E977}}
	\def\iquoter{{\IcoMoon\char"E978}}
	\def\iwrench{{\IcoMoon\char"E991}}
	\def\ieqh{{\IcoMoon\char"E992}}
	\def\ieqv{{\IcoMoon\char"E993}}
	\def\icog{{\IcoMoon\char"E994}}
	\def\icogs{{\IcoMoon\char"E995}}
	\def\istats{{\IcoMoon\char"E99B}}
	\def\iwinnerflag{{\IcoMoon\char"E9CC}}
	\def\iwarning{{\IcoMoon\char"EA07}}
	\def\inotification{{\IcoMoon\char"EA08}}
	\def\iquestion{{\IcoMoon\char"EA09}}
	\def\iinfo{{\IcoMoon\char"EA0C}}
	\def\icancel{{\IcoMoon\char"EA0D}}
	\def\ialphaaasc{{\IcoMoon\char"EA48}}
	\def\ialphaddesc{{\IcoMoon\char"EA49}}
	\def\inumberasc{{\IcoMoon\char"EA4A}}
	\def\inumberdesc{{\IcoMoon\char"EA4B}}
	\def\iorderasc{{\IcoMoon\char"EA4C}}
	\def\iorderdesc{{\IcoMoon\char"EA4D}}
	\def\iboxdone{{\IcoMoon\char"EA52}}
	\def\iboxundone{{\IcoMoon\char"EA53}}
	\def\iradiodone{{\IcoMoon\char"EA54}}
	\def\iradiodonenegative{{\IcoMoon\char"EA55}}
	\def\iradioundone{{\IcoMoon\char"EA56}}
	\def\isuperscript{{\IcoMoon\char"EA69}}
	\def\icodeopentag{{\IcoMoon\char"EA7F}}
	\def\icodeclosetag{{\IcoMoon\char"EA80}}
	\def\iterminal{{\IcoMoon\char"EA81}}
	\def\imail{{\IcoMoon\char"E900}}
	\def\iwindow{{\IcoMoon\char"E906}}
	\def\icpu{{\IcoMoon\char"E907}}
	\def\ieye{{\IcoMoon\char"E908}}
	\def\icomplexcox{{\IcoMoon\char"E901}}
	\def\ibug{{\IcoMoon\char"E902}}
	\def\iattachment{{\IcoMoon\char"E909}}
	\def\ilabel{{\IcoMoon\char"E90A}}
	\def\ibookmark{{\IcoMoon\char"E90B}}
	\def\ibadge{{\IcoMoon\char"E90C}}
	\def\iuser{{\IcoMoon\char"E903}}
	\def\ibusinessman{{\IcoMoon\char"E904}}
	\def\ibusinesswoman{{\IcoMoon\char"E905}}
	\def\iidea{{\IcoMoon\char"E90D}}
	\def\isettings{{\IcoMoon\char"E90E}}
	\def\ifatinfo{{\IcoMoon\char"E90F}}
	\def\iclock{{\IcoMoon\char"E910}}
	\def\itimer{{\IcoMoon\char"E911}}
	\def\iflag{{\IcoMoon\char"E912}}
	\def\iwinnercup{{\IcoMoon\char"E913}}
	\def\igraduate{{\IcoMoon\char"E917}}
        \def\igithub{{\IcoMoon\char"EAB0}}


	\newfontfamily\IcoFont{IcoFont}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
	]

	\def\imail{{\IcoFont\char"EF12}}
	\def\igraduate{{\IcoFont\char"EADB}}
	\def\iid{{\IcoFont\char"EF4A}}
	\def\isettings{{\IcoFont\char"EFE1}}
	\def\isettingsalt{{\IcoFont\char"EC83}}
	\def\iterminalalt{{\IcoFont\char"F00A}}
	\def\iauto{{\IcoFont\char"EEA9}}
	\def\ifile{{\IcoFont\char"EB08}}
	\def\ifilecode{{\IcoFont\char"EB0C}}
	\def\ibook{{\IcoFont\char"EAD1}}
	\def\ibookmark{{\IcoFont\char"EEC0}}



	
\makeatother

% Define fonts
\makeatletter
	\newfontfamily\Lato{Lato}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *-Regular,
		BoldFont = *-Bold,
		ItalicFont = *-Italic,
		BoldItalicFont = *-BoldItalic
	]	

	\newfontfamily\Scientifica{scientifica}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		BoldFont = *Bold,
		ItalicFont = *Italic,
	]

	\newfontfamily\FiraCode{FiraCode}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *-Regular,
		BoldFont = *-Bold,
		Contextuals=Alternate
	]

	\newfontfamily\LatoThin{Lato-Thin}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		ItalicFont = *Italic,
	]	

	\newfontfamily\LatoLight{Lato-Light}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		ItalicFont = *Italic,
	]	

	\newfontfamily\LatoBlack{Lato-Black}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		ItalicFont = *Italic,
	]	
	
	\newfontfamily\Karla{Karla}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *-Regular,
		BoldFont = *-Bold,
		ItalicFont = *-Italic,
		BoldItalicFont = *-BoldItalic
	]	

	\newfontfamily\Agency{Agency}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
	]
	
	\newfontfamily\Alte{Alte DIN 1451 Mittelschrift}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		BoldFont=*,
		ItalicFont=*,
		BoldItalicFont=*,
		BoldFeatures={FakeBold=2},
		ItalicFeatures={FakeSlant=0.25},
		BoldItalicFeatures={FakeBold=2, FakeSlant=0.25},
	]	

	\newfontfamily\AlteG{Alte DIN 1451 Mittelschrift G}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *,
		BoldFont=*,
		ItalicFont=*,
		BoldItalicFont=*,
		BoldFeatures={FakeBold=2},
		ItalicFeatures={FakeSlant=0.25},
		BoldItalicFeatures={FakeBold=2, FakeSlant=0.25},
	]	

	\newfontfamily\Gobold{Gobold}[
		Path = content/fonts/,
		Extension = .otf,
		UprightFont = *-Regular,
		BoldFont=*-Bold,
		ItalicFont=*-Italic,
		BoldItalicFont=*-BoldItalic,
	]

	\newfontfamily\GoboldHollow{GoboldHollow}[
		Path = content/fonts/,
		Extension = .otf,
		UprightFont = *-Regular,
		BoldFont=*-Bold,
		ItalicFont=*-Italic,
		BoldItalicFont=*-BoldItalic,
	]

	\newfontfamily\Mononoki{mononoki}[
		Path = content/fonts/,
		Extension = .ttf,
		UprightFont = *-Regular,
		BoldFont=*-Bold,
		ItalicFont=*-Italic,
		BoldItalicFont=*-BoldItalic,
	]
\makeatother

%% Document Style
\makeatletter
	%% Global 
	\setlength\parindent{0pt}
	\setlength\parskip{0.75em}
	\setlength{\headsep}{2cm}

	%% Define no Par Skip
	\let\svpar\par
	\edef\svparskip{\the\parskip}
	\def\revertpar{\svpar\setlength\parskip{\svparskip}\let\par\svpar}
	\def\noparskip{\leavevmode\setlength\parskip{0pt}\def\par{\svpar\let\par\revertpar}}

	%% Chapter
	\setcounter{chapter}{-1}
	\def\currentchapter{}
	\titlespacing*{\chapter}{0pt}{-10pt}{30pt}

	\titleformat{\chapter}[frame]
		{\setlength{\fboxrule}{5pt}\color{primary!85!black}}
		{\hspace{0.25cm}\fontsize{260}{0}\selectfont\AlteG \textcolor{primary!20!white}{\thechapter}\hspace{0.25cm}}
		{1cm}
		{\color{primary}\fontsize{30}{42}\selectfont\Gobold\centering\chaptertitlename: #1\global\def\currentchapter{#1}}

	\titleformat{name=\chapter,numberless}[frame]
		{\setlength{\fboxrule}{5pt}\color{primary!85!black}}
		{}
		{1cm}
		{\color{primary}\fontsize{30}{42}\selectfont\Gobold\centering #1\global\def\currentchapter{#1}}

	%% Table of Contents
	\titlecontents*{chapter}
		[0pt]
		{\addvspace{0.5cm}}
		{\color{primary!60!black}\fontsize{12}{0}\selectfont\Gobold\thecontentslabel\hspace{0.125cm}\color{primary}}
		{}
		{\color{primary!80!black}\hfill\bfseries\Scientifica\fontsize{12}{0}\selectfont\contentspage\hrule height 1pt width \textwidth\relax}

	\titlecontents{section}
		[0.5cm]
		{}
		{\color{primary!60!black}\fontsize{10}{0}\selectfont\AlteG\thecontentslabel\hspace{0.125cm}\color{primary}}
		{}
		{\color{primary!80!black}\hfill\bfseries\Scientifica\fontsize{10}{0}\selectfont\contentspage}

	\titlecontents{subsection}
		[1cm]
		{}
		{\color{primary!60!black}\fontsize{8}{0}\selectfont\Lato\thecontentslabel\hspace{0.125cm}\color{primary}}
		{}
		{\color{primary!80!black}\hfill\bfseries\Scientifica\fontsize{8}{0}\selectfont\contentspage}

	%% Section
	\titlespacing*{\section}{0pt}{3mm}{5mm}	
	\titleformat{\section}[hang]
	{}
	{\rlap{\color{primary!85!black}\rule[-6pt]{\textwidth}{1.2pt}}\colorbox{primary!85!black}{%
		\raisebox{0pt}[13pt][3pt]{ \makebox[60pt]{% height, width
					\fontsize{15}{12}\AlteG\color{white}{\thesection}}
			}}}%
	{15pt}%
	{\color{primary}\fontsize{20}{12}\selectfont\Gobold#1\hspace{\fill}\ibook}

	%% Subsection
	\titlespacing*{\subsection}{0pt}{3mm}{0pt}	
	\titleformat{\subsection}[hang]
		{\color{primary!20!black}\fontsize{12}{12}\selectfont\Lato}
		{\thesubsection\fontsize{8}{6}\selectfont\ibookmark\hspace{10pt}}
		{0pt}
		{\color{accent!65!black}#1}
	
	%% Abstract
	\renewenvironment{abstract}
		{\thispagestyle{empty}\vfill{\par\raggedleft\fontsize{16}{18}\selectfont\Gobold\color{primary!75!black} Estratto\par\vspace{0.25cm}\hrule height 2pt \relax\par\noparskip}%
		\setlength{\parskip}{0.5em}\color{primary!35!black}\fontsize{12}{10}\selectfont\Lato}
		{\newpage}


	%% Highlight
	\def\hi#1{{\color{accent!80!black}\LatoBlack\mbox{#1}}}
	\def\dir#1{{\color{primary!80!black}\Mononoki\mbox{\penalty 100\ifolder\hspace{1pt}#1}}}
	\def\file#1{{\color{accent!80!white}\Mononoki\mbox{\penalty 100\ifile\hspace{1pt}#1}}}

	%% Scale text size using current font size
	\def\t@scale#1{\fontsize{#1\dimexpr\f@size pt\relax}{\dimexpr\f@size pt\relax}\selectfont}
	\def\t@apex@measure#1#2{\raisebox{#2\dimexpr\f@size pt\relax}{\t@scale{#2}#1}}
	\def\t@apex#1{\t@apex@measure{#1}{0.65}}
	\def\sp@text#1#2{{#1\t@scale{0.7}\t@apex{#2}}}
	\def\sp@rtext#1#2{{\t@scale{0.7}\t@apex{#2}}{#1}}

	\def\dir#1{{\color{primary!75!black}\sp@rtext{#1}{\ifolder}}}	
	\def\qmake{\sp@text{gnu make}{\iauto}}
	\def\qmakefile{\sp@text{makefile}{\ifile\iauto}}
	\def\qterm{{\color{primary}\sp@rtext{terminal emulator}{\iterminal}}\ }
	\def\qstruct#1{{\color{primary}\t@apex@measure{struct}{0.5}\sp@text{#1}{\iwrench}}}
	\def\qfunction#1{{\color{cherryred}\sp@text{#1}{\ifile\icodeopentag}}}

	\newcommand{\mycbox}[1]{\tikz{\path[draw=#1,fill=#1] (0,0) rectangle (1cm,1cm);}}

	%% Footer & Header

	\fancypagestyle{luftmensch@style}{
		\fancyhf{}
		\fancyhead[L]{}
		\fancyhead[C]{}
		\fancyhead[R]{}
		\renewcommand{\headrule}{}

		\fancyfoot[L]{{\fontsize{10}{0}\selectfont\Lato\color{primary}InfoPoint}}
		\fancyfoot[C]{{\fontsize{14}{0}\selectfont\bfseries\Scientifica{\color{primary}\thepage}}}
		\fancyfoot[R]{{\fontsize{10}{0}\selectfont\Gobold\color{primary}\currentchapter\hspace{2pt}\ibook}}
		\renewcommand{\footrule}{{\color{primary}\hrule height 1pt width \textwidth \relax}}
	}
\makeatother

% Color palette
\colorlet{primary}{sapphire}
\colorlet{accent}{violet}

% Define page layout(s)
\geometry{ a4paper, 
	margin = 7.5mm,
	bottom = 12mm,
	footskip = 3mm,
	heightrounded,
	nohead,
	nomarginpar }

% Tikz 
\usetikzlibrary{calc, arrows, shapes.geometric}

\tikzset{
	mpath/.style={
		fill=#1,
		draw=#1,
		line width=0.1pt
	},
	square/.style={regular polygon,regular polygon sides=4, inner sep=0pt, outer sep=0pt},
}

\newcommand\coverpage{%
	\newgeometry{noheadfoot=true, margin=0pt}\newpage\thispagestyle{empty}%
	\noindent\begin{tikzpicture}[remember picture, overlay, shift=(current page.south west)]%
		\begin{scope}[x={(current page.south east)},y={(current page.north west)}, overlay]
			% Background
			\fill [primary!75!white] (0,0) rectangle (1,1);

			%% Layout 
			% Text box
			\path [mpath=primary!25!white]  (0,0.25) -- (0.2,0.4) -- (0.8, 0.4) -- (1, 0.55) -- (1, 0.1) -- (0.93, 0.05) -- (0.07, 0.05) -- (0,0) -- cycle;
			% Left Wing
			\path [mpath=primary!85!white]	(0,0.27) -- (0.17,0.40) -- (0.2, 0.40) -- (0,0.25) -- cycle;
			% Right Wing
			\path [mpath=primary!85!white]	(0.77,0.4) -- (0.8, 0.40) -- (1, 0.55) -- (1, 0.57) -- cycle;
			% Under Wing 
			\path [mpath=primary!65!black]  (0,0) -- (0.025,0) -- (0.075, 0.035) -- (0.94, 0.035) -- (1, 0.08) -- (1, 0.1) -- (0.93, 0.05) -- (0.07, 0.05) -- (0, 0) -- cycle;
			% Central Wing 
			\path [mpath=primary!35!black]	(0,0.27) -- (0.17,0.40) -- (0.77, 0.40) -- (1, 0.57) -- (1, 0.8) -- (0.85, 0.8) -- (0.6, 0.6) -- (0.13, 0.6) -- (0,0.5) -- cycle;

			%% Text nodes
			% Icon 
			\node (fiisymbol) at ([yshift=-0.5cm, xshift=0.5cm]0,1)[align=center, anchor=north west, inner sep=0pt, outer sep=0pt]
				{ \color{primary!65!black}\includegraphics[%
						width=3cm,%
						height=3cm,%
						keepaspectratio%
					] {content/img/uni_logo.pdf}};

			\node (fiitext) at ([xshift=0.25cm] fiisymbol.north east) [align=left, anchor=north west]
				{{\color{primary!65!black}\Lato\fontsize{10}{0}\selectfont Università degli Studi di Napoli}};
			\node (fiiname) at ([xshift=0.01cm, yshift=0.2cm]fiitext.south west) [align=left, anchor=north west]
				{{\color{primary!65!black}\Agency\fontsize{24}{0}\selectfont Federico II}};

			% Date and academic year
			\node (academicyear) at ([xshift=-0.5cm] fiitext.north -| 1,1) [align=right, anchor=north east] 
				{{\color{primary!65!black}\Gobold\fontsize{26}{0}\selectfont A.A.\ 2022-2023}};

			% Title of the documentation
			% TODO: Position of text 
			\node at ([xshift=0.1cm, yshift=0.1cm] $(0,0)!0.5!(1,1)$) [align=center, anchor=center, inner sep=0pt, outer sep=0pt] 
				{{\color{primary!10!black}\Gobold\fontsize{72}{0}\selectfont Info}{\color{primary!10!black}\Gobold\fontsize{50}{0}\selectfont Point}};
			\node at ($(0,0)!0.5!(1,1)$) [align=center, anchor=center, inner sep=0pt, outer sep=0pt] 
				{{\color{primary!85!white}\Gobold\fontsize{72}{0}\selectfont Info}{\color{primary!70!white}\Gobold\fontsize{50}{0}\selectfont Point}};

			\node at ([yshift=-0.31cm, xshift=-0.170cm]0.77, 0.40) [align=center, anchor=north east, inner sep=0pt, outer sep=0pt]
				{\color{primary!10!black}\itshape\fontsize{18}{12}\selectfont\Gobold ID Gruppo: <TODO>};
			\node at ([yshift=-0.25cm, xshift=-0.125cm]0.77, 0.40) [align=center, anchor=north east, inner sep=0pt, outer sep=0pt]
				{\color{primary!85!white}\itshape\fontsize{18}{12}\selectfont\Gobold ID Gruppo: <TODO>};

			%% Authors
			% Author 1
			\node (auth1graduate) at ([xshift=1cm, yshift=1.5cm] 0.07, 0.05) []
				{{\color{primary!80!black}\fontsize{26}{0}\selectfont\igraduate}};
			\node (auth1name) at ([xshift=0.05cm] auth1graduate.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{18}{0}\selectfont Valentino Bocchetti}};
			\node (auth1mailcon) at ([xshift=0.05cm] auth1name.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\imail}};
			\node (auth1mail) at ([xshift=0.025cm] auth1mailcon.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont vale.bocchetti@studenti.unina.it}};
			\node (auth1imatr) at ([xshift=0.15cm] auth1mail.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\iid}};
			\node (auth1matr) at ([xshift=0.05cm] auth1imatr.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont N86003405}};

			% Separator
			\path [mpath=primary] ([xshift=0.15cm, yshift=0.15cm] auth1graduate.north) -- ([xshift=0.25cm, yshift=0.25cm]auth1graduate.north)
				-- ([xshift=0.65cm, yshift=0.25cm] auth1matr.east |- auth1graduate.north) -- ([xshift=0.5cm, yshift=0.15cm] auth1matr.east |- auth1graduate.north) -- cycle;

			% Author 2
			\node (auth2graduate) at ([xshift=0.40cm, yshift=0.40cm] auth1graduate.north) [anchor=south west]
				{{\color{primary!80!black}\fontsize{26}{0}\selectfont\igraduate}};
			\node (auth2name) at ([xshift=0.05cm] auth2graduate.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{18}{0}\selectfont Dario Morace}};
			\node (auth2mailcon) at (auth1mailcon.north |- auth2graduate.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\imail}};
			\node (auth2mail) at ([xshift=0.025cm] auth2mailcon.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont <TODO>@studenti.unina.it}};
			\node (auth2imatr) at (auth1imatr.north |- auth2mail.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\iid}};
			\node (auth2matr) at ([xshift=0.05cm] auth2imatr.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont <TODO>}};

			% Separator 2
			\path [mpath=primary] ([xshift=0.15cm, yshift=0.15cm] auth2graduate.north) -- ([xshift=0.25cm, yshift=0.25cm]auth2graduate.north)
				-- ([xshift=0.65cm, yshift=0.25cm] auth2matr.east |- auth2graduate.north) -- ([xshift=0.5cm, yshift=0.15cm] auth2matr.east |- auth2graduate.north) -- cycle;

			% Author 3
			\node (auth3graduate) at ([xshift=0.40cm, yshift=0.40cm] auth2graduate.north) [anchor=south west]
				{{\color{primary!80!black}\fontsize{26}{0}\selectfont\igraduate}};
			\node (auth3name) at ([xshift=0.05cm] auth3graduate.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{18}{0}\selectfont Lucia Brando}};
			\node (auth3mailcon) at (auth2mailcon.north |- auth3graduate.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\imail}};
			\node (auth3mail) at ([xshift=0.025cm] auth3mailcon.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont <TODO>@studenti.unina.it}};
			\node (auth3imatr) at (auth2imatr.north |- auth3mail.east) [anchor=west]
				{{\color{primary!80!black}\fontsize{14}{0}\selectfont\iid}};
			\node (auth3matr) at ([xshift=0.05cm] auth3imatr.east) [anchor=west]
				{{\color{primary!80!black}\Alte\fontsize{12}{0}\selectfont <TODO>}};

		\end{scope}%
	\end{tikzpicture}\restoregeometry\newpage}

\newcommand\credits{%
	\newgeometry{noheadfoot=true, margin=0pt}\newpage\thispagestyle{empty}%
	\noindent\begin{tikzpicture}[remember picture, overlay, shift=(current page.south west)]%
		\begin{scope}[x={(current page.south east)},y={(current page.north west)}, overlay]%
			% Background
			\path [mpath=accent!15!white] (0,0.5) rectangle (1,1);
			\path [mpath=primary!15!white] (0,0) rectangle (1,0.5);

			% Characterize Background
			\path [mpath=accent!15!white] (0,0.5) rectangle (0.15,0.4);
			\path [mpath=primary!15!white] (1,0.5) rectangle (0.85,0.6);
			\path [mpath=primary!35!white] (0,0) rectangle (1,0.025);
			\path [mpath=accent!35!white] (0,1) rectangle (1,0.975);

			% Heading
			\node (header) at ([xshift=0.5cm] 0, 0.975) [inner sep=0pt, outer sep=0pt, anchor=north west]
				{\color{primary}\fontsize{20}{20}\selectfont };

			\path [draw=primary, line width=3pt] (0, 0.75) -- ([xshift=2cm] 0.125, 0.75) -- ($([xshift=2cm] 0.125, 0.75)!0.5!([xshift=-2cm] 0.875, 0.25)$);
			\path [draw=accent, line width=3pt]  ($([xshift=2cm] 0.125, 0.75)!0.5!([xshift=-2cm] 0.875, 0.25)$) --  ([xshift=-2cm] 0.875, 0.25) -- (1, 0.25);

                        % Auth-Block-1
                        \node (auth1-block-img) at(current page.center) {\includegraphics[width=3cm]{content/img/luftmensch-luftmensch.png}};

			\node (auth1-block-name) at ([xshift=0.05cm, yshift=-0.6cm] auth1-block-img.north east) [anchor=north west]
				{\color{primary}\fontsize{20}{20}\selectfont\Gobold Valentino\hspace{3pt}Bocchetti};
			\node (auth1-block-matr-icon) at (auth1-block-name.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\iid};
			\node (auth1-block-matr-text) at (auth1-block-matr-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont N86003405};
			\node (auth1-block-mail-icon) at ([xshift=0.45cm] auth1-block-matr-icon.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\imail};
			\node (auth1-block-mail-text) at (auth1-block-mail-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont vale.bocchetti@studenti.unina.it};
			\node (auth1-block-git-icon) at ([xshift=0.45cm] auth1-block-mail-icon.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\iuser};
			\node (auth1-block-git-text) at (auth1-block-git-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont \href{https://github.com/luftmensch-luftmensch/}{\hi{Profilo}}};

			% Auth-Block-2
			\node (auth2-block-img) at (0.125, 0.75) [anchor=west, circle, minimum width=4cm,
				path picture={\node at (path picture bounding box.center) [anchor=center] {\includegraphics[width=3cm]{content/img/lbrando.png}};}]{};
			\node (auth2-block-name) at ([xshift=0.05cm, yshift=-0.6cm] auth2-block-img.north east) [anchor=north west]
				{\color{primary}\fontsize{20}{20}\selectfont\Gobold Lucia\hspace{3pt}Brando};
			\node (auth2-block-matr-icon) at (auth2-block-name.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\iid};
			\node (auth2-block-matr-text) at (auth2-block-matr-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont <TODO>};
			\node (auth2-block-mail-icon) at ([xshift=0.45cm] auth2-block-matr-icon.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\imail};
			\node (auth2-block-mail-text) at (auth2-block-mail-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont <TODO>@studenti.unina.it};
			\node (auth2-block-git-icon) at ([xshift=0.45cm] auth2-block-mail-icon.south west) [anchor=north west, square]
				{\color{primary}\fontsize{16}{20}\selectfont\iuser};
			\node (auth2-block-git-text) at (auth2-block-git-icon.east) [anchor=west, align=left]
				{\color{primary}\fontsize{14}{20}\selectfont  \href{https://github.com/lbrando/}{\hi{Profilo}}};

			% Auth-Block-3
			\node (auth3-block-img) at (0.875, 0.25) [anchor=east, circle, minimum width=4cm,
				path picture={\node at (path picture bounding box.center) [anchor=center] {\includegraphics[width=3cm]{content/img/goblino.png}};}]{};
			\node (auth3-block-name) at ([xshift=-0.10cm, yshift=-0.6cm] auth3-block-img.north west) [anchor=north east]
				{\color{accent!80!black}\fontsize{20}{20}\selectfont\Gobold Dario\hspace{3pt}Morace};
			\node (auth3-block-matr-icon) at (auth3-block-name.north east) [anchor=south east, square]
				{\color{accent!80!black}\fontsize{16}{20}\selectfont\iid};
			\node (auth3-block-matr-text) at (auth3-block-matr-icon.west) [anchor=east, align=right]
				{\color{accent!80!black}\fontsize{14}{20}\selectfont <TODO>};
			\node (auth3-block-mail-icon) at ([xshift=-0.45cm] auth3-block-matr-icon.north east) [anchor=south east, square]
				{\color{accent!80!black}\fontsize{16}{20}\selectfont\imail};
			\node (auth3-block-mail-text) at (auth3-block-mail-icon.west) [anchor=east, align=right]
				{\color{accent!80!black}\fontsize{14}{20}\selectfont <TODO>@studenti.unina.it};
			\node (auth3-block-git-icon) at ([xshift=-0.45cm] auth3-block-mail-icon.north east) [anchor=south east, square]
				{\color{accent!80!black}\fontsize{16}{20}\selectfont\iuser};
			\node (auth3-block-git-text) at (auth3-block-git-icon.west) [anchor=east, align=right]
				{\color{accent!80!black}\fontsize{14}{20}\selectfont \href{https://github.com/saltyDario/}{\hi{Profilo}}};

		\end{scope}
	\end{tikzpicture}\restoregeometry\newpage}

% LstListing
\makeatletter
	\lst@Key{firstlineandnumber}\relax{\def\lst@firstline{#1\relax}\def\lst@firstnumber{#1\relax}}
\makeatother

\lstset{%
	autogobble=true,
	style=FiraCodeStyle,
	backgroundcolor=\color{naplesyellow!10!white},
	commentstyle=\itshape\color{seagreen},
	keywordstyle=\color{cherryred},
	stringstyle=\color{naplesyellow!80!black},
	basicstyle=\linespread{1.15}\footnotesize\FiraCode,
	breaklines=true,
	tabsize=2,
  escapeinside={(*@}{@*)},
	xleftmargin=0.5cm,
	xrightmargin=0.5cm,
	framesep=0mm,
	extendedchars=true,
	showstringspaces=false,
	showtabs=false,
	showstringspaces=false,
	captionpos=b,
	title=\color{primary}\fontsize{10}{12}\selectfont\sp@rtext{\lstname}{\ifilecode},
	columns=fixed }

\lstdefinestyle{wnumbers}{
	% Style of numbers 
	xleftmargin=1cm,
	numbers=left,
	numberstyle=\Lato\scriptsize\color{orange!80!black},
	frame=l,
	framesep=0.5cm,
	framexleftmargin=0.3cm,
	rulecolor=\color{white},
	fillcolor=\color{naplesyellow!40!white}
}

\lstdefinelanguage{makefile}{%
	morecomment=[l][commentstyle]{\#},%
}

\lstdefinelanguage[POSIX]{C}
	[]{}
	{ alsoletter={\#}, 
		sensitive=true, 
		%% Handle directives
		moredelim=*[s][{\color{violet!60!white}}]{\#include\ <}{.h>},
		moredelim=*[l][{\color{blue!65!white}}]\#if,
		moredelim=*[l][{\color{blue!65!white}}]\#endif,
		moredelim=*[s][{\color{violet!60!white!70!black}}]{\#include\ "}{.h"},
		moredelim=*[l][{\color{blue!90!white!70!black}}]\#define,
		moredelim=*[s][{\color{turquoise!70!black}}]{[}{]},
		%% Comments
		comment=[l]//,
		morecomment=[s]{/*}{*/},
		% Strings
		string=[b]{"},
		morestring=[b]{'},
		% Modifiers 
		keywords=[0]{const, unsigned, signed, static, volatile, typedef, struct, union, enum, atomic_t},
		% Primitives 
		keywords=[1]{int, float, double, long, short, char, void, bool},
		% Logical constructs 
		keywords=[2]{if, else, return, for, while, do},
		% Operators
		otherkeywords={*, &},
		keywords=[3]{*, &},
		% API structs
		keywords=[8]{sockaddr\_in, sockaddr, transport, pthread\_t, ssize\_t, size\_t, epoll\_event, timeval},
		% API functions 
  	keywords=[9]{epoll\_event, epoll\_wait, epoll\_ctl, send, recv, close, open, read, write, exit, assert, perror, gettimeofday},
		% API Constants 
		keywords=[10]{EPOLLIN, EPOLLET, EPOLL\_CTL\_ADD, EPOLL\_CTL\_DEL, false, true, errno, NULL, MSG\_PEEK, MSG\_NOSIGNAL},
		% OWN structs
		keywords=[11]{handler, socket, server, event, client, connection, conn, status, conn\_status, waiting\_room},
		% OWN structs
		keywords=[12]{PRCLEAR, PRCHAT, READY, CHAT},
		% Colors
		%  TODO: Move elsewhere
		directivestyle=\color{blue!85!white},
		keywordstyle=[0]\color{cherryred},
		keywordstyle=[1]\color{green!75!black},
		keywordstyle=[2]\color{cherryred},
		keywordstyle=[3]\color{naplesyellow!75!black},
		keywordstyle=[8]\color{seagreen!80!black},
		keywordstyle=[9]\color{pink!70!black},
		keywordstyle=[10]\color{turquoise!80!black},
		keywordstyle=[11]\color{sapphire!80!black},
		keywordstyle=[12]\color{turquoise!70!black},
		}[keywords,comments,strings,directives]

% Itemize, Enumerate, Description
\setlist{leftmargin=*,noitemsep,topsep=0pt,parsep=0pt,partopsep=0pt, after=\vspace{0.5em}}
\setlist[enumerate, 1]{label=\Roman*.}
\setlist[enumerate, 2]{label=\arabic*.}
\setlist[enumerate, 3]{label=\alph*.}
\setlist[itemize, 1]{label=$\smallblacktriangleright$}
\setlist[itemize, 2]{label=$\smalldiamond$}
\setlist[itemize, 3]{label=$\smallcircle$}


% Hooks
\AtBeginDocument{\Karla\pagestyle{luftmensch@style}}
