## A voir:
- Making Changes to a Remote Project | GitHub Tutorial Part 2: https://www.youtube.com/watch?v=nlF-SOrod5o

-----------------------------------------------------------------
## En bref
Pense-bête GitHub pour travail en équipe

#### 1. Créer une nouvelle branche
`git checkout -B USER_NAME/BRANCH_NAME`
#### 2. Aller dans une branche existante
`git checkout BRANCH_NAME`
#### 3. Ajouter et committer des fichiers dans la branche
`git add FILE_NAME`
`git commit -m "MESSAGE"`
`git push origin USER_NAME/BRANCH_NAME`
#### 4. Mettre à jour la branche avec main (éviter les conflits)
Avant de pousser des modifications, assure-toi que ta branche est à jour avec main:
`git checkout main`
`git pull origin main`
`git checkout USER_NAME/BRANCH_NAME`
`git merge main`
Si un conflit apparaît, il faut le résoudre, puis:
`git add .`
`git commit -m "Résolution de conflit"`
`git push origin USER_NAME/BRANCH_NAME`
**VOIR RÉSOLUTION DE CONFLITS PLUS BAS POUR PLUS DE DÉTAILS**
#### 5. Créer une Pull Request sur GitHub
	1. Allez sur GitHub et ouvrez une Pull Request en respectant la mise en page suivante:
	2. ## What has been done?
		Décrivez le travail réalisé.
	3. ## Usage
		Expliquez comment utiliser le fichier ou la fonctionnalité ajoutée.
#### 6. Demander une revue du code
	- Ajouter des reviewers pour approbation du code.
	- Attendre les retours et appliquer les corrections si nécessaire.
#### 7. Supprimer une branche après fusion une fois la `Pull Request` validée et fusionnée:
`git checkout main`
`git pull origin main`
`git branch -d USER_NAME/BRANCH_NAME`
`git push origin --delete USER_NAME/BRANCH_NAME`


## Résolution de conflits
Si ta branche est en retard par rapport à `main` et que des changements ont été faits sur les mêmes fichiers, il y a un risque de **conflits** lorsque tu voudras fusionner ta branche via une Pull Request.

**Pourquoi mettre à jour ta branche avec `main` ?**
L'idée est de récupérer les dernières mises à jour de `main` avant de pousser ton travail, pour:
✅ Éviter les conflits au moment de la fusion.
✅ Tester que ton code fonctionne avec les nouvelles modifications.
✅ S'assurer que ton travail est bien basé sur la dernière version du projet.

**Comment mettre à jour ta branche avec `main` ?**
Tu dois d'abord récupérer la dernière version de `main`, puis fusionner ces changements dans ta branche:
#### Aller sur la branche principale et récupérer les dernières modifications
`git checkout main`
`git pull origin main`
#### Revenir sur ta branche et fusionner main dedans
`git checkout USER_NAME/BRANCH_NAME`
`git merge main`
Si tout se passe bien, tu auras juste un message de confirmation. Mais si des **conflits** apparaissent (c'est-à-dire que les mêmes fichiers ont été modifiés sur `main` et ta branche), Git te demandera de les résoudre.

**Que faire en cas de conflit ?**
(1. Ouvre les fichiers concernés : Git ajoute des marqueurs `<<<<`, `====`, et `>>>>` pour indiquer les conflits.)
2. Modifie le fichier pour choisir quelle version garder (ou fusionner les deux).
3. Une fois résolu, ajoute le fichier corrigé :
`git add NOM_DU_FICHIER`
4. Puis termine la fusion avec un commit :
`git commit -m "RESOLUTION_MESSAGE"`
5. Enfin, pousse les changements mis à jour :
`git push origin USER_NAME/BRANCH_NAME`

-----------------------------------------------------------------


###### The Three States

|   |   |
|---|---|
|`Git Directory`|The .git directory is where Git stores the metadata and object database for the repository|
|`Working Directory`|A copy of one version of the git project, taken from compressed database in the .git directory|
|`Staging Area/Index`|File that stores information about what will next be committed into the git repository|

###### Configure Tooling

|   |   |
|---|---|
|`git config --global user.name "[name]"`|Sets the name you want attached to your commit transactions|
|`git config --global user.email "[email address]"`|Sets the email you want attached to your commit transactions|
|`git config --global color.ui auto`|Enables helpful colorizations of command line input|

###### Create Repositories

|   |   |
|---|---|
|`git init [project-name]`|Creates a new local repository with the specified name|
|`git clone [url]`|Downloads a project and its entire version history|

###### Make Changes

|   |   |
|---|---|
|`git status`|Lists all new or modified files to be committed|
|`git diff`|Shows file differences not yet staged|
|`git add [file]`|Snapshots the file in preparation for versioning|
|`git diff --staged`|Shows file differences between staging and the last file version|
|`git reset [file]`|Unstages the file, but preserves its contents|
|`git commit -m "[descriptive message]"`|Records the file snapshots permanently in version history|

###### Group Changes

|                                        |                                                                    |
| -------------------------------------- | ------------------------------------------------------------------ |
| `git branch`                           | Lists all local branches in the current repository                 |
| `git checkout -B emonacho/hello-world` | Creates new branch.                                                |
| `git branch [branch-name]`             | Creates a new branch                                               |
| `git checkout [branch-name]`           | Switches to the specified branch and updates the working directory |
| `git merge [branch]`                   | Combines the specified branch's history into the current branch    |
| `git branch -d [branch-name]`          | Deletes the specified branch                                       |
| `git remote add [remote-name] [url]`   | Add a new remote git repository as a shortname                     |
| `git remote -v`                        | Lists all remote git repositories                                  |

###### Refactor Filenames

|   |   |
|---|---|
|`git rm [file]`|Deletes the file from the working directory and stages the deletion|
|`git rm --cached [file]`|Removes the file from version control but preserves the file locally|
|`git mv [file-original] [file-renamed]`|Changes the file name and prepares it for commit|

###### Suppress Tracking

|   |   |
|---|---|
|`*.log` `build/` `temp-*`|A text file named .gitignore suppresses accidental versioning of files and paths matching the specified patterns|
|`git ls-files --other --ignored --exclude-standard`|Lists all ignored files in this project|

###### Save Fragments

|   |   |
|---|---|
|`git stash`|Temporarily stores all modified tracking files|
|`git stash save [message]`|Save local modifications to a new stash|
|`git stash pop`|Restores the most recently stashed files|
|`git stash list`|Lists all stashed changesets|
|`git stash show`|Show the changes recorded in the stash|
|`git stash drop`|Discards the most recently stashed changeset|

###### Review History

|   |   |
|---|---|
|`git log`|Lists version history for the current branch|
|`git log --follow [file]`|Lists version history for a file, including renames|
|`git diff [first-branch]...[second-branch]`|Shows content differences between two branches|
|`git show [commit]`|Outputs metadata and content changes of the specified commit|

###### Redo Commits

|   |   |
|---|---|
|`git reset [commit]`|Undoes all commits after [commit], preserving changes locally|
|`git reset --hard [commit]`|Discards all history and changes back to the specified commit|

###### Synchronize Changes

|   |   |
|---|---|
|`git fetch [bookmark] [branch]`|Downloads all history from the repository bookmark, optionally specifying branch|
|`git merge [bookmark]/[branch]`|Combines bookmark's branch into current local branches|
|`git push [alias] [branch]`|Uploads all local branch commits to GitHub|
|`git push [alias] :[branch]`|Deletes remote branch|
|`git pull`|Downloads bookmark history and incorporates changes|
|`git pull --rebase`|Downloads bookmark history and incorporates your changes on top of remote changes|
|`git rebase --interactive --autosquash HEAD~N`|Squash N last commits|
|`git cherry-pick -n <sha>`|Cherry-pick a commit|
|`git revert -n <sha>`|Revert a commit|

###### Debugging

|                    |                                                                 |
| ------------------ | --------------------------------------------------------------- |
| `git blame [file]` | Show what revision and author last modified each line of a file |
| `git bisect`       | Use binary search to find the commit that introduced a bug      |
