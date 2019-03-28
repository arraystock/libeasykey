#!/bin/sh

setup_git() {
  git config --global user.email "travis@travis-ci.org"
  git config --global user.name "Travis CI"
}

commit_website_files() {
  git checkout --orphan travis-build-$COMMIT_TAG
  mkdir libeasykey
  mv *.zip libeasykey/
  git add libeasykey/*
  git commit --message "libeasykey | Commit $COMMIT_TAG"
}

upload_files() {
  git remote add origin-build https://${GH_TOKEN}@github.com/arraystock/builds.git > /dev/null 2>&1
  git push --quiet --set-upstream origin-build master
}

setup_git
commit_website_files
upload_files
