#!/bin/bash

########################################################
#                                                      #
#  Script made to send one specific macro to SLURM     #
#                                                      #
########################################################

function print_help() {
    echo "SCRIPT: send_macro.sh"
    echo "====================="
    echo "./send_macro.sh --macro <macro> --opt <options> --time <time>"
    echo "Where:"
    echo "  <macro>   = selects specific macro"
    echo "  <options> = add options - IMPORTANT: between single quotes and parenthesis, exactly like the example"
    echo "  <time>    = request time (in hours)"
    echo "Example:"
    echo "  ./send_macro.sh --macro eta_bkg-fitting/Make_BkgFitting.cxx --opt '("C", "Q2", 0, "png")' --time 1"
    exit
}

function process_args() {
    arr=("$@")
    ic=0
    while [[ $ic -le $((${#arr[@]}-1)) ]]; do
        if [[ "${arr[$ic]}" == "--macro" ]]; then
            macro=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--opt" ]]; then
            options=${arr[$((ic+1))]}
        elif [[ "${arr[$ic]}" == "--time" ]]; then
            time=${arr[$((ic+1))]}
        else
            echo "ERROR: unrecognized argument: ${arr[$((ic))]}.";
            print_help;
        fi
        ((ic+=2))
    done
}

function print_args() {
    echo "SCRIPT: send_macro.sh"
    echo "====================="
    echo "macro   = ${macro}"
    echo "options = ${options}"
    echo "time    = ${time} hr"
    echo ""
}

################
###   Main   ###
################

# check for errors
if [[ -z "${WORKDIR}" ]]; then
    echo "ERROR: variable WORKDIR is unset."
    exit 1
fi

if [[ -z "${PRODIR}" ]]; then
    echo "ERROR: variable PRODIR is unset."
    exit 1
fi

if [[ ${#} -ne 6 ]]; then
    echo "ERROR: ${#} arguments were provided, they must be 6."
    print_help
fi

argArray=("$@")
process_args "${argArray[@]}"
print_args

# define important dirs
TMPDIR=${PRODIR}/tmp/${macro%/*}
mkdir -p ${TMPDIR}

# convert options into one string
s_options=${options%)*}
s_options=${s_options#(*}
s_options=${s_options//'"'/}
s_options=${s_options//, /_}

jobname=${macro##*/}
jobname=${jobname%.cxx}_${s_options}
jobfile="${TMPDIR}/${jobname}.sh"

echo "#!/bin/bash"                            > ${jobfile}
echo "#SBATCH -J ${jobname}"                 >> ${jobfile}
echo "#SBATCH -o ${TMPDIR}/${jobname}.out"   >> ${jobfile}
echo "#SBATCH -e ${TMPDIR}/${jobname}.err"   >> ${jobfile}
echo "#SBATCH --time=${time}:00:00"          >> ${jobfile}
echo "#SBATCH --mem=1GB"                     >> ${jobfile}
echo ""                                      >> ${jobfile}
echo "source ${HOME}/.bashrc"                >> ${jobfile}
echo "set-root"                              >> ${jobfile}
echo "export WORKDIR=${WORKDIR}"             >> ${jobfile}
echo "export PRODIR=${PRODIR}"               >> ${jobfile}
echo "cd ${PRODIR}/macros"                   >> ${jobfile}
echo "root -l -b -q '${macro}${options}'"    >> ${jobfile}

echo "Submitting job: ${jobfile}"
sbatch ${jobfile} # submit job!
