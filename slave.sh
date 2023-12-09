find . -name "*.exe" -exec rm '{}' \;

if [ "$#" -ne 1 ]; then
    echo ":("
    exit 1
fi

git add .
git commit -m "$1"
git push