# Taches Minishell

**Input utilisateur**

**LEXER**
- Découpe la ligne en tokens (mots, pipes, redirections…)
- Gère les quotes
- Attribue un type à chaque token

**PARSER**
- Vérifie la validité syntaxique
- Construit l’AST (arbre de commandes)
**HEREDOC HANDLING (étape intermédiaire)**
- Identifie les heredocs dans l’AST
- Demande à l’utilisateur le contenu
- Prépare les entrées temporaires

**EXPANSION**
- Remplace les variables (`$VAR`)
- Développe les wildcards (`*`)
- Supprime les quotes

**EXECUTION**
- Gère les redirections
- Crée les pipes si besoin
- Lance les commandes (builtins ou execve)
- Fork et gestion des processus
  
**Résultat affiché dans le terminal**
