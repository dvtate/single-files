#!/bin/bash
set -e

function get_repo_name {
    # $1 --" "https://github.com/user/repo --> echo 'repo'"
    url_components=(${1//\// })             # split by /
    last_index="$((${#url_components[@]} - 1))"     # give last element
    echo ${url_components[last_index]}
    # echo ${url_components[-1]}
}

function mk_form {
    local repo="$(get_repo_name $2)"
    mkdir "build_$repo"
    cd "build_$repo"

    # edit overlay template
    # cp ../overlay.tex .
    # sed -i -e 's|projectname|'"$1"'|g' overlay.tex
    # sed -i -e 's|projecturl|'"$2"'|g' overlay.tex
    cat "
\documentclass[a4paper]{article}

%\usepackage{lmodern}    % Latin Modern
%\usepackage{tgheros}   % Helvetica
\usepackage{tgtermes}  % Times
%\usepackage{tgcursor}  % Courier

% adapt default font
%  * serif:      \rmdefault
%  * sans-serif: \sfdefault
%  * monospace:  \ttdefault
%\renewcommand*\familydefault{\sfdefault}
\usepackage[T1]{fontenc}
\usepackage[utf8]{inputenc}
\usepackage{xcolor}
\usepackage{tikz}
\usepackage{url}

\newcommand\PlaceText[3]{%
\begin{tikzpicture}[remember picture,overlay]
\node[outer sep=0pt,inner sep=0pt,anchor=south west] 
  at ([xshift=#1,yshift=-#2]current page.north west) {#3};
\end{tikzpicture}%
}

\begin{document}
    \nopagecolor            % transparent background
    \pagenumbering{gobble}  % remove page numbers

    \PlaceText{400}{280}{$1}
    \PlaceText{325}{335}{\url{$2}}

\end{document}
    " > overlay.tex

    pdflatex overlay.tex
    pdflatex overlay.tex
    pdftk overlay.pdf background ../template.pdf output "$repo.pdf"
    cp "$repo.pdf" ../forms/

    cd ..
    
    rm -rf "build_$repo"

    echo "Rendered $repo.pdf"
}

# Render forms
mk_form "Conway Game of Life OS" "https://github.com/dvtate/conway-OS"
mk_form "Postfix Haskell VSCode" "https://github.com/dvtate/ph-syntax"
mk_form "Discord Inactivity Bot" "https://github.com/dvtate/discord-inactivity-bot"
mk_form "Single-Files" "https://github.com/dvtate/single-files"
mk_form "Blog" "https://github.com/dvtate/blog"
mk_form "Ideas" "https://github.com/dvtate/ideas"
mk_form "http://old.dvtt.net" "https://github.com/dvtate/old.dvtt.net"
mk_form "fake-traffic" "https://github.com/dvtate/fake-traffic"
mk_form "Link in Bio" "https://github.com/dvtate/link-in-bio"
mk_form "dotfiles" "https://github.com/dvtate/dotfiles"
mk_form "XSSFaaS" "https://github.com/dvtate/XSSFaaS"
mk_form "Terminal Colors" "https://github.com/dvtate/terminal-colors"
mk_form "cookie-cpp" "https://github.com/dvtate/cookie-cpp"
mk_form "me.dvtt.net" "https://github.com/dvtate/me.dvtt.net"
mk_form "Postfix Haskell" "https://github.com/dvtate/postfix-haskell"
mk_form "Discord RSS Bot" "https://github.com/dvtate/discord-bot-rs"
mk_form "xTie.net" "https://github.com/dvtate/xtie.net"
mk_form "dnsssim" "https://github.com/dvtate/dnssim"
mk_form "LoL Item Counters" "https://github.com/dvtate/lol-item-counters"
mk_form "Cookie Monster Plugin" "https://github.com/dvtate/cookie-monster-plugin"
mk_form "Tokipona Japonese" "https://github.com/dvtate/tokipona-japanese"
mk_form "dvtt.net" "https://github.com/dvtate/dvtt.net"
mk_form "lang-spec" "https://github.com/dvtate/lang-spec"
mk_form "Phlappy Bird" "https://github.com/dvtate/phlappy-bird"
mk_form "Breakout" "https://github.com/dvtate/breakout"
mk_form "SCL" "https://github.com/dvtate/SCL"
mk_form "Planning" "https://github.com/dvtate/planning"
mk_form "anti-spellcheck" "https://github.com/dvtate/anti-spellcheck"
mk_form "Tokipona Runes" "https://github.com/dvtate/tokipona-runes"
mk_form "3D models" "https://github.com/dvtate/3D"
mk_form "Alphavantage API" "https://github.com/dvtate/alphavantage-api"
mk_form "RoboBibb Website" "https://github.com/RoboBibb/robobibb.github.io/"
mk_form "@dvtt YouTube Channel" "https://www.youtube.com/@dvtt"

