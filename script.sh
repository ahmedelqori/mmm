ARG=$(pgrep minishell)
cd /proc/"$ARG"/fd || { echo "Error: Couldn't change directory"; exit 1; }
ls -l
