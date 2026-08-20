# syntax=docker/dockerfile:1

# Base image for the CMake development container.
#
# This is one of the images our CI infrastructure uses, described under
# `.gitlab/ci/docker/`, so the development environment closely matches the
# environment in which merge requests are tested.  Override this build
# argument in `devcontainer.json` to select a different base image.
ARG BASE_IMAGE=kitware/cmake:ci-debian13-x86_64-2026-04-28

FROM ${BASE_IMAGE}

ARG USERNAME=cmake-dev
ARG USER_UID=1000
ARG USER_GID=${USER_UID}

# Install tools that are useful for development but not needed by CI.
RUN apt-get update \
 && apt-get install -y --no-install-recommends \
      bash-completion \
      ccache \
      cmake \
      gdb \
      less \
      man-db \
      nano \
      ninja-build \
      nodejs \
      npm \
      openssh-client \
      python3-sphinx \
      vim \
 && rm -rf /var/lib/apt/lists/*

# Install `clang-format` version 18, exactly, as required by our style rules,
# along with `pre-commit` to run the checks configured by our
# `.pre-commit-config.yaml`.  Neither is available from the distribution in a
# suitable version, so install them from Python wheels.
RUN python3 -m venv /opt/cmake-dev \
 && /opt/cmake-dev/bin/pip install --no-cache-dir \
      'clang-format==18.1.8' \
      pre-commit \
 && ln -s /opt/cmake-dev/bin/clang-format /usr/local/bin/clang-format \
 && ln -s /opt/cmake-dev/bin/clang-format /usr/local/bin/clang-format-18 \
 && ln -s /opt/cmake-dev/bin/pre-commit /usr/local/bin/pre-commit

# Install the GitLab CLI, `glab`, and `glab-axi`, an agent-ergonomic wrapper
# around it, for interacting with our GitLab instance.
COPY install_glab.sh /tmp/
RUN sh /tmp/install_glab.sh \
 && rm /tmp/install_glab.sh

# Create an unprivileged user matching the typical host account so that files
# created in the mounted source tree are not owned by `root`.
RUN groupadd --gid ${USER_GID} ${USERNAME} \
 && useradd --uid ${USER_UID} --gid ${USER_GID} --create-home --shell /bin/bash ${USERNAME} \
 && echo "${USERNAME} ALL=(ALL) NOPASSWD:ALL" > /etc/sudoers.d/${USERNAME} \
 && chmod 0440 /etc/sudoers.d/${USERNAME}

# Pre-create the directories that `devcontainer.json` mounts volumes over so
# that the volumes inherit the ownership recorded here.
RUN install -d -o ${USERNAME} -g ${USERNAME} \
      /home/${USERNAME}/.cache/ccache \
      /home/${USERNAME}/.config/glab-cli

# Run the optional local customization scripts.  They are ignored by Git so
# that developers may customize the container without modifying tracked files
# or risking that the customizations end up in a commit.  See
# `Help/dev/devcontainer.rst`.
COPY hooks/ /opt/cmake-dev-hooks/
RUN if test -f /opt/cmake-dev-hooks/root.sh; then sh -e /opt/cmake-dev-hooks/root.sh; fi

USER ${USERNAME}
RUN if test -f /opt/cmake-dev-hooks/user.sh; then sh -e /opt/cmake-dev-hooks/user.sh; fi
